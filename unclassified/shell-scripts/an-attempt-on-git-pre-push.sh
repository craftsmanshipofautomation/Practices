# 变量
project="/home/root_/Desktop/editor"
temp_dir=~/git_temp
main_branch="_s"
## 这个脚本的版本基础
base_commit="830cf84bd900e169b01898667"


# 清理
rm -rf ${temp_dir}
# 如果中转站存在, 删掉
if [[ -e ${temp_dir} ]]
then
        rm ${temp_dir} -rf
fi
mkdir -p ${temp_dir}


cd ${project}
git checkout ${main_branch}
# 此分支用于上传
git branch -D dev3_push
git branch dev3_push
git checkout dev3_push
# 获取 HEAD 的 comment
# - 删掉 1~3 行, 删掉空行, 删掉前面的空格
last_comment=$(git log -1 |sed '1,3d'|sed '/^$/d' |sed "s/^[ \t]*//")
git reset ${base_commit}
bash clear.sh
# .gitignore 什么时候生效呢: 假如 a 还没被忽略,reset到HEAD~1,再 commit
# 这样原本被提交的 a, 就被此次提交忽略
git add .
git commit -m ${last_comment}

# separators
IFS=$'\n'
diffs=$(git diff dev --name-status)


echo "=============================================="
echo "=============================================="
echo "=============================================="


for diff in ${diffs}
do
    a="a"
    #echo "--name-status: " ${diff}
done

# array
to_be_rms=()
to_be_replaceds=()



#http://tldp.org/LDP/abs/html/string-manipulation.html
for diff in ${diffs}
do
        # 截取第一个字母(但还有其他状态: 比如 R074, rename, 74% similarity)
        status=${diff:0:1}
        # status=$(echo ${diff} | awk "{print $1;}")
        # ${string%substring}
        # 删掉最后一个 / 及其之后的所有字符, 获取这个文件所在的目录
        dir=""
        if [[ ${status} == "R" ]] || [[ ${status} == "C" ]]
        then
                file=$(echo ${diff} | awk '{print $3;}')
                dir=${file%/*}
        else
                file=$(echo ${diff} |sed "s/[MAD]\s*\(.*\)/\1/g")
                dir=${file%/*}
        fi
        dir_depth1_to_hold_modification=""
        # if it is a dir
        if [[ ${dir} == *"/"* ]]
        then
            #echo dir: ${dir}
            dir_depth1_to_hold_modification=${temp_dir}/${dir}
        # else it is a file
        # 如果是根目录的文件
        else
            dir_depth1_to_hold_modification=${temp_dir}/
        fi


        if [[ ${status} == "D" ]]
        then
                to_be_rms+=(${file})
        elif [[ ${status} == "R" ]] || [[ ${status} == "C" ]]
        then
                s=$(echo ${diff} | awk '{print $1;}')
                old=$(echo ${diff} | awk '{print $2;}')
                new=$(echo ${diff} | awk '{print $3;}')
                echo "status: "${s}
                echo "to be removed: "${old}
                echo "will be copied to push branch: "${new}
                # 将 new 拷到提交分支
                to_be_replaceds+=(${new})
                # 将 old 从提交分支删掉
                to_be_rms+=(${old})
                mkdir -p ${dir_depth1_to_hold_modification}
                cp ${new} ${dir_depth1_to_hold_modification}
        else
                to_be_replaceds+=(${file})
                mkdir -p ${dir_depth1_to_hold_modification}
                cp ${file} ${dir_depth1_to_hold_modification}
        fi
done

for f in ${to_be_rms[@]}
do
    a="a"
    #echo "to_be_rms: "${f}
done

for f in ${to_be_replaceds[@]}
do
    a="a"
    #echo "to_be_replaced: "${f}
done

# 切换到提交分支
git checkout dev

for to_be_rm in ${to_be_rms[@]}
do
        # 删除提交分支上该被删除的部分
        rm ${to_be_rm}
done

for diff in ${to_be_replaceds[@]}
do
        file=$(echo ${diff} |sed "s/^[MAD]\s*\(.*\)/\1/g")
        dir=${file%/*}
        abs_path=${temp_dir}/${file}
        cp ${abs_path} ${dir}
done


git add .
git commit -m "${last_comment}"

rm -rf ${temp_dir}
