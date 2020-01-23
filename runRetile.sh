#!/bin/sh
if [ "$#" -ne 6 ]; then
  echo "Illegal number of parameters"
  echo "USAGE: $0 <EXEC> <INPUT PREFIX> <OUTPUT PREFIX> <NUMBER OF FRAMES> <NUMBER OF ITERATIONS> <FACTOR FOR TARGET NUMBER OF OUTPUT VERTICES>"
  exit
fi
echo "Binary file: " $1
echo "Input filename: " $2
echo "Output filename: " $3
echo "Number of frames to retile: " $4
echo "Number of iterations: " $5
echo "Output vertex count factor: " $6

#for i in {1..240}
for i in `seq 1 $4`;
do
  INPUTFILE=""
  INPUTFILE=$2$INPUTFILE$i".obj"


  OUTPUTFILE=""
  OUTPUTFILE=$3$OUTPUTFILE$i".obj"
  
  echo "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+"
  date
  echo "Input frame: "$INPUTFILE

  $1 -o $OUTPUTFILE -i $5 -f $6 $INPUTFILE

  echo "Output frame: "$OUTPUTFILE
  date
  echo "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+="
  
done
