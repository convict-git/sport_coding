#! /bin/bash
if timeout 3 /usr/bin/time --output="errlog" --format="(%M kb, %e sec)" ./a.out < input1 > crap ; then                                 #If program runs in specified runtime
  echo -e "\n\e[48;5;237m               Input File                   \e[0m"
  echo -e "Crap"
  cat crap
  echo -e "Error"
  # cat errlog
  var=$(<errlog)
  echo -e "\e[32mHere is the answer $var\e[0m"
fi
