#!/bin/bash

PROG_NAME="getMp3Info"
TEST_DATA_DIR="test_data"


function print_line() { 
    echo "-------------------------------------------"
}

function print_error_and_exit() {
    echo 
    print_line
    echo " ERROR : $1 "
    print_line
    echo 
    exit 1
}

function print_info() {
    echo 
    print_line
    echo " info : $1 "
    print_line
    echo 

}




function prepare_test_content() {
    
    if [ -d ./tmp ]; then
        print_info " old test content available. Removing test content ..."
        rm -rf ./tmp
    fi
    
    mkdir ./tmp
    mkdir ./tmp/$TEST_DATA_DIR

    cp -rf $DATA_DIR/* ./tmp/test_data/

    i=0;
    FILE_NAME_PATTERN="test_file_${i}.mp3"

    for file in ./tmp/test_data/* 
    do 
        FILE_NAME_PATTERN="test_file_${i}.mp3"
        mv "$file" ./tmp/$TEST_DATA_DIR/${FILE_NAME_PATTERN}
        i=$(expr $i + 1 )
        echo " Prepare test content : $file >>>>> $FILE_NAME_PATTERN"
    done
  
} 


function usage() {
	echo " Usage:"
	echo "      $1 <mp3_file_dir>"
	exit -1	
}

if [ -z $1 ] ;  then 
	usage $0
fi

DATA_DIR=$1

command -v ${PROG_NAME} 2>&1 > /dev/null 

if [ "$?" != "0" ] ; then
	print_error_and_exit " The program might be incorrect or programe not found in cureent directory"

fi

if [ ! -d ${DATA_DIR} ]; then
    print_error_and_exit " Data dir not found"
fi

prepare_test_content

echo "---------- starting test for ${PROG_NAME} ------------"
ErrorCode=""
ErrorCount=0;
for file in ./tmp/$TEST_DATA_DIR/*; 
do
    print_info "Proccessing $file "
    ${PROG_NAME} $file
    ErrorCode=$?

    if [ "$ErrorCode" == "255" ]; then
        ErrorCount=$(expr $ErrorCount + 1 )
        continue
    fi

    if [ "$ErrorCode" != "0" ]; then
        ErrorCount=$(expr $ErrorCount + 1 )
        print_error_and_exit " Error code : $ErrorCode -- Error count : $ErrorCount -- Failed to run command  : ./${PROG_NAME} $file"
    fi


done
        print_info "Error count : $ErrorCount"

rm -rf ./tmp
