
# @author Dylan Perdigão       -   2018233092
# @author Ana Rita Rodrigues   -   2018284515

#I/O
inputDIR="input"
outputDIR="output"

if test -f "main"; then
    rm main
fi

g++ -o main main.cpp

for file_path in "$inputDIR"/*; do
    #CRIAR OS FICHEIROS OUTPUT
    file=$(basename "$file_path")
    outfile=${file%.*}.out
    ./main < $file_path > "$outputDIR"/$outfile
done

