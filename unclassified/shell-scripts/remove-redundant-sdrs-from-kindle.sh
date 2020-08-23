# turn space to ~~

for d in *\ *
do
	tmp="${d// /~~}"
    mv "$d" ${tmp}
	echo [去除空格] ${d} === ${tmp}
done

# do job

folders=$(ls -d *.sdr)
for d in ${folders}
do
	check=0
	f1=$(echo "${d}" | sed s'/sdr/mobi/g')
	f2=$(echo "${d}" | sed s'/sdr/azw3/g')
	if [ -f "${f1}" ]
	then
		check=1
	elif [ -f "${f2}" ]
	then
		check=1
	fi
	if [ ${check} -ne 1 ]
	then
		rm "${d}" -r
		echo [删除成功] "${d}"
	fi
done


# turn ~~ to space back

for d in *~~*
do
	tmp="${d//~~/ }"
    mv "$d" "${tmp}"
	echo [还原空格] "${d}" === "${tmp}"
done
