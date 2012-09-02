#!/bin/bash
starttime=$(date +%s) #seconds since 1970-01-01 00:00:00 UTC
echo We started at $starttime on machine $(hostname)
sleep 5
endtime=$(date +%s)
((time = endtime - starttime))
echo It takes $time seconds
echo It takes $((endtime - starttime)) seconds
echo $(echo $(echo $(echo $(echo Too much nested))))
