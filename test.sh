testFiles=`ls ./test/*.test.c`
allErrors=0
index=1
errorNames=()
green() {
    echo -e "\e[32m"
}
red() {
    echo -e "\e[33m"
}
reset() {
    echo -e "\e[0m"
}
for eachfile in $testFiles
do
    let index=${index}+1
    green
    echo "---------------"
    reset
    echo "Running tests for File:"
    echo "  $eachfile"
    echo ""
    chrlen=${#eachfile}
    chrlenMin=`expr $chrlen - 2`
    nameNoC=$(echo $eachfile | cut -c1-$chrlenMin)
    nameNoPath=$(echo $eachfile | cut -c8-$chrlenMin)
    mkdir -p ./test/bin
    gcc $eachfile -o ./test/bin/$nameNoPath
    ./test/bin/$nameNoPath
    if [ $? -eq 1 ]
    then
        errorNames+=($eachfile)
        ((allErrors=allErrors+1))
    fi
    echo ""
    echo "End of File:"
    echo "  $eachfile"
    green
    echo "---------------"
    reset
done

if [ $allErrors -gt 0 ]
then
    red
    echo "XXXXX---------XXXXX"
    printf "Number of failed test-files: %d\n" $allErrors
    echo "Failed test-files:"
    for value in "${errorNames[@]}"
    do
        echo "  $value"
    done
    echo "XXXXX---------XXXXX"
    reset
else
    green
    echo "#####---------#####"
    echo "All test-files completed successfully!"
    echo "#####---------#####"
    reset
fi