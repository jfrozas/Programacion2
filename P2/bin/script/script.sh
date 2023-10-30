#!/bin/bash

#para dar formato
ROJO=`tput setaf 1`
VERDE=`tput setaf 2`
AMARILLO=`tput setaf 3`
RESET=`tput sgr0`
SUBR=`tput smul`

#Comprobar que existen en path actual los ficheros output de referencia
#(sino, tal y como está el script da un OK a pesar de mostrar un error en el diff)
function check_files {
    REF=$1
    for file in ${REF[@]}
    do
        if [ ! -f "${file}.txt" ]
        then
            printf "${ROJO}Please add the reference file ${file}.txt to the current path${RESET}\n"
            exit 1
        fi
    done
}

# Funcion para comprobar la salida del programa
# Parametros de entrada:
#   - main
#   - dependencias
#   - ficheros de entrada
#   - ficheros de referencia
#   - salida verbosa
# Parametros de salida:
#   - Exito (1) o fallo (0) en la comprobacion
function check_output {
    MAIN=$1
    DEPS=$2
    VERBOSE=$3
    
    echo ${MAIN}
    
    
    check_files ${ficherosRef}

    rm -f ${MAIN}

    printf "${AMARILLO}Running script..."
    printf "\n${AMARILLO}Compiling "$MAIN" program with\ngcc -Wall -Wextra ${DEPS} ${MAIN}.c -o ${MAIN}${RESET}\n"



    gcc -Wall -Wextra ${DEPS} ${MAIN}.c -o ${MAIN}

    if [ -f ${MAIN} ]
    then
        allOK=1
        printf "\n${AMARILLO}Checking "$MAIN" program output...\n${RESET}"
	    printf "\n${SUBR}Input file${RESET}                          ${SUBR}Result${RESET}  ${SUBR}Notes${RESET}\n"
      for index in ${!ficherosEntrada[*]}
	    do
            nombre=${ficherosEntrada[$index]}
            ficheroEntrada="$nombre".txt
            if [ "$ficheroEntrada" = ".txt" ]; then
                ficheroEntrada="(no input file)"
                ficheroSalida="${MAIN}_output.txt"
            else
                ficheroSalida="$nombre"_output.txt
            fi
            ficheroReferencia=${ficherosRef[$index]}.txt
            ficheroDiff="$nombre"_diff.txt
            ./${MAIN} $ficheroEntrada > $ficheroSalida
            diff -w -B -b -y --suppress-common-lines --width=100 $ficheroReferencia $ficheroSalida > $ficheroDiff
            iguales=$(stat -c%s $ficheroDiff)
            
            if [ ${iguales} -eq "0" ]
            then
                printf "%-35s %-12s %s\n" "$ficheroEntrada" "${VERDE}OK"  "${RESET}Verified on ${ficheroReferencia}"
            else
                printf "%-35s %-12s %s\n" "$ficheroEntrada" "${ROJO}FAIL" "${RESET}Check ${ficheroReferencia} and ${ficheroSalida}"
                allOK=0
                if  ${VERBOSE}
                then
                    printf '\nFile: %-39s | File: %s\n' $ficheroReferencia $ficheroSalida
                    printf '=%.0s' {1..100}
                    printf '\n'
                    cat ${ficheroDiff}
                    printf '\n'
                fi
            fi
	    	rm $ficheroDiff
	    done
    else
   		allOK=0
	    printf "\n${ROJO}Compilation failed${RESET}"
    fi
	printf "\n\n"
    return ${allOK}
}

function show_result {
    MESSAGE=$1
    RESULT=$2
    printf "${AMARILLO}${MESSAGE} "
    if  [ ${RESULT} -eq 1 ]
    then
        printf "${VERDE}OK${RESET}"
    else
        printf "${ROJO}FAIL${RESET}"
    fi
    printf "\n\n"
}


MAIN_NAME=main

usage() { echo "Usage: $0 [-p <main|test>] [-v]" 1>&2; exit 1; }

# Comprobar parametros de entrada
VERBOSE=false
while getopts "p:v" opt; do
    case "$opt" in
      p)  MAIN_NAME=$OPTARG
          if [[ "$MAIN_NAME" != "main" && "$MAIN_NAME" != "test" ]]; then
            usage
          fi
          ;;
      v)
          VERBOSE=true
          echo VERBOSETRUE
          ;;
      *)
          usage
          ;;
    esac
done
if [ "$MAIN_NAME" = "main" ]
then
  ficherosEntrada=("script_minimos/rem")
  ficherosRef=("script_minimos/rem_ref")
  check_output main "video_list.h video_list.c user_list.h user_list.c" ${VERBOSE}
  MAIN_OK=$?
  show_result "Global result:" $MAIN_OK
  printf "\n"
  
else
  ficherosEntrada=("")
  ficherosRef=("script_test/test_video_list_ref")
  check_output "test/test_video_list" "video_list.h video_list.c" ${VERBOSE}
  TEST_VIDEO_LIST_OK=$?
  show_result "Test video list result:" $TEST_VIDEO_LIST_OK
  printf "\n"
  
  ficherosRef=("script_test/test_user_list_ref")
  check_output "test/test_user_list" "video_list.h video_list.c user_list.h user_list.c" ${VERBOSE}
  TEST_USER_LIST_OK=$?
  show_result "Test user list result:" $TEST_USER_LIST_OK
  printf "\n"
  
  ALL_OK=$((${TEST_USER_LIST_OK} * ${TEST_VIDEO_LIST_OK}))
  show_result "Global result:" $ALL_OK
  printf "\n"
  
  
fi


