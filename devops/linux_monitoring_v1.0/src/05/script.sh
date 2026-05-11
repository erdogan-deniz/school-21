#!/bin/bash

path=$1

print_chislo_papok(){
    echo "- Количество папок: $(find . -type d | wc -l)"
}

print_top5(){
    echo "- Топ 5 папок с самым большим весом в порядке убывания (путь и размер):
$(sudo du -a "$1" | sort -n -r | head -n 5)"
}

print_all(){
    echo "- Общее число файлов: $(ls -l | grep "^-" | wc -l)"
}

print_conf(){
    echo "- Number of:"
	echo -n "Configuration files (with the .conf extension) = " ; find "$path" -type f -name '*.conf' | wc -l
	echo -n "Text files = "; find "$path" -type f -exec grep -Iq . {} \; -print | wc -l
	echo -n "Executable files = " ; find "$path" -type f -executable | wc -l
	echo -n "Log files (with the extension .log) = " ; find "$path" -type f -name '*.log' | wc -l
	echo -n "Archive files = " ; find "$path" -type f \( -name '*.tar' -o -name '*.zip' -o -name '*.7z' \) | wc -l
	echo -n "Symbolic links = " ; find "$path" -type l | wc -l
}

print_isp_top10(){
    echo "- TOP 10 files of maximum size arranged in descending order (path, size and type):"
	mapfile -t top_files < <(find "$path" -type f -exec du -h {} + | sort -rh | head -10)
	for i in "${!top_files[@]}"; do
		file_path="${top_files[$i]}"
		if [[ -n "$file_path" ]]; then
			size=$(echo "$file_path" | awk '{print $1}')
			fpath=$(echo "$file_path" | awk '{print $2}')
			ext=$(echo "$fpath" | grep -o -E '\.[^/.]+$' | sed 's/^\.//')
			echo "$((i + 1)) - $fpath, $size, $ext"
		fi
	done
}

print_big_top10(){
    echo "- TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):"
	mapfile -t top_exec < <(find "$path" -executable -type f -exec du -h {} + | sort -rh | head -10)
	for i in "${!top_exec[@]}"; do
		file_path="${top_exec[$i]}"
		if [[ -n "$file_path" ]]; then
			size=$(echo "$file_path" | awk '{print $1}')
			fpath=$(echo "$file_path" | awk '{print $2}')
			md5=$(md5sum "$fpath" | awk '{print $1}')
			echo "$((i + 1)) - $fpath, $size, $md5"
		fi
	done
}
