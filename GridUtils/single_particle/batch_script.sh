#!/bin/bash
umask 002
echo "Process Number"
echo $PROCESS
whoami
uname -a
cat /etc/issue
cat /proc/cpuinfo

export DISPLAY=0

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunetpc v09_25_00 -q e20:prof
setup cmake v3_20_0
setup gcc v9_3_0

filelist=$1
mymacro_full=$2
outputpath=$3

my_condor_work=${_CONDOR_SCRATCH_DIR}/work

mkdir -p ${my_condor_work}
cd ${my_condor_work}

ifdh cp --cp_maxretries=1 -D $filelist ./
listname=`basename "$filelist"`

let num=$PROCESS*1+1
echo $listname $num
input=$(tail -n+${num} $listname | head -n1)

#inputfile=$(echo $input | awk -F'/' '{print $NF}')
inputpath=`dirname "$input"`
inputfile=`basename "$input"`

mymacro=`basename "$mymacro_full"`

#search=.$(echo $output_prefix | awk -F'.' '{print $NF}')
#replace=_$PROCESS$search
#output="OUTPUTPREFIX_ar40_evtEVTNUM_${startIdx}_${stopIdx}.root"

echo Input: ${inputpath}/${inputfile}
echo Copy Input file and My Macro
ifdh cp --cp_maxretries=1 -D ${input} ./
ifdh cp --cp_maxretries=1 -D ${mymacro_full} ./
chmod 777 ${mymacro}
ls -lhrt

output=$(cat ${inputfile} | grep 'fileName' | awk -F' ' '{print $2}')
output_log=log_${output%.root}.log
echo Ouput: ${output}

echo Run my macro
#echo root -l -q -b `printf "${mymacro}(\"$inputfile\",$pdg,\"$output\")" ` # make text file with real det. resolution
#root -l -q -b `printf "${mymacro}(\"$inputfile\",$pdg,\"$output\")" ` | tee ${output_log}
./${mymacro} $inputfile | tee ${output_log}
echo "Done my macro"
ls -lhrt

echo "Copying out files"
echo ${output} to ${outputpath}
ifdh cp --cp_maxretries=1 -D ${output} ${outputpath} || exit 14
ifdh cp --cp_maxretries=1 -D ${output_log} ${outputpath} || exit 16

cd ${_CONDOR_SCRATCH_DIR}
rm -rf *
ls -lhrt