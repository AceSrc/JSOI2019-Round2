while true
do
  ./mk > input
  ./b < input > output_a
  ./bf < input > output_bf
  if [ $? != 0 ]
  then
    exit 1
  else
    echo "AC"
  fi 
done
