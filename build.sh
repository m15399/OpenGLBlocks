#!/bin/bash

CXX="clang++"
INCLUDES="-I /usr/local/include"
LIBRARIES="-L /usr/local/lib -lSDL2 -framework OpenGL"
CXX_FLAGS="-Wall -g -std=c++14"

IN_FILES="*.cpp"
IN_FILES="${IN_FILES} GridGame/*.cpp"


# Create unity file

UNITY_FILE="__unity__.cpp"
TMP_UNITY_FILE="/tmp/__unity__.cpp"
rm -f $UNITY_FILE
rm -f $TMP_UNITY_FILE

echo "#include \"SDL.h\"" > ${TMP_UNITY_FILE}
cat ${IN_FILES} >> ${TMP_UNITY_FILE}

mv ${TMP_UNITY_FILE} ${UNITY_FILE}


# Compile

COMMAND="${CXX} ${INCLUDES} ${LIBRARIES} ${CXX_FLAGS} ${UNITY_FILE}"
bash -c "${COMMAND}"
RET=$?


# Clean up

if [ $RET -eq 0 ]; then
	# rm $UNITY_FILE
	echo
fi

exit $RET
