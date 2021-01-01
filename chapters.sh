chapterFiles=`ls ./chapters/chapter*.c`
chapters=()
echo "Select the number of the chapter you want to run:"
COUNTER=1
for I in ${chapterFiles[@]}
    do  
        echo ${COUNTER}
        chapters+=($COUNTER)
        ((COUNTER++))
    done

read SELECTED_CHAPTER
SELECTED_CHAPTER=${SELECTED_CHAPTER:-1}
isInArray=false
for value in "${chapters[@]}"
    do
        if [ $value == $SELECTED_CHAPTER ]
        then
            isInArray=true
        fi
    done

if [ $isInArray == true ]
then
    echo "Chapter selected: $SELECTED_CHAPTER"
    mkdir -p ./chapters/bin
    gcc ./chapters/chapter$SELECTED_CHAPTER.c -o ./chapters/bin/chapter$SELECTED_CHAPTER
    ./chapters/bin/chapter$SELECTED_CHAPTER
else
    echo "Given number is not a selectable chapter."
fi