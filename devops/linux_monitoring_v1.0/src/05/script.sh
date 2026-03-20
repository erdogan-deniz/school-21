#!/bin/bush

path=$1

print_chislo_papok(){
    echo "- Количество папок: $(find . -type d | wc -l)"
}

print_top5(){
    echo "- Топ 5 папок с самым большим весом в порядке убывания (путь и размер):
$(sudo du -a $1 | sort -n -r | head -n 5)"
}

print_all(){
    echo "- Общее число файлов: $(ls -l | grep "^-" | wc | awk '{print $1}')"
}

print_conf(){
    echo "- Number of:"
	echo -n "Configuration files (with the .conf extension) = " ; find $path -type f -name \*.conf | wc -l
	echo -n "Text files = "; find $path* -type f -exec grep -Iq . {} \; -print | wc -l
	echo -n "Executable files = " ; find $path -type f -executable | wc -l
	echo -n "Log files (with the extension .log) = " ; find $path -type f -name \*.log | wc -l
	echo -n "Archive files = " ; find $path -type f -name \*.tar -o -name \*.zip -o -name \*.tar -o -name \*.7z | wc -l
	echo -n "Symbolic links = " ; ls -lR $path | grep ^l | wc -l
}

print_isp_top10(){
    echo "- TOP 10 files of maximum size arranged in descending order (path, size and type):"
	for i in {1..10}
	do
		file_path=$(find $path -type f -exec du -h {} + | sort -rh | head -10 | sed "${i}q;d") # найти по пути файлы, выполнить ду | сортировка реверс | top10 | взять ном строку, выйти очистить буфер
		if ! [[ -z $file_path ]]
		then
			echo -n "$i - "
			echo -n "$(echo $file_path | awk '{print $2}'), " # path
			echo -n "$(echo $file_path | awk '{print $1}'), " # size
			echo "$(echo $file_path | grep -o -E "\.[^/.]+$" | awk -F . '{print $2}')" # extension
		fi
	done
}

print_big_top10(){
    echo "- TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):"
  	for i in {1..10}
  	do
		file_path=$(find $path -executable -type f -exec du -h {} + | sort -rh | head -10 | sed "${i}q;d")
		if ! [[ -z $file_path ]]
		then
			echo -n "$i - "
			echo -n "$(echo $file_path | awk '{print $2}'), "
			echo -n "$(echo $file_path | awk '{print $1}'), "

			npath=$(echo $file_path | awk '{print $2}')
			MD5=$(md5sum $npath | awk '{print $1}')
			echo "$MD5"
		fi
	done
}
