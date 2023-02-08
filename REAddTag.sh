commit_list=$(git log --pretty=format:"%H,")
echo ${commit_list}

array=(${commit_list//,/ })  
 
for var in ${array[@]}
do
   echo $var
   echo ".............................."
   echo ""

   git show $var
done 