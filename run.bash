compression='compress.cpp'
decompression='decompress.cpp'

if command -v clang++ &> /dev/null; then
    clang++ $compression lib/compression.cpp -o compress.exe
    clang++ $decompression lib/compression.cpp -o decompress.exe
    compile_status=$?
elif command -v g++ &> /dev/null; then
    g++ $compression lib/compression.cpp -o compress.exe
    g++ $decompression lib/compression.cpp -o decompress.exe
    compile_status=$?
else
    echo -e "clang++ and g++ not found!\nEither install them or edit the run.bash file and add the C++ compiler present in the system."
    exit 1
fi

if [ $compile_status -ne 0 ]; then
    echo "Compilation failed. Please check for errors."
    exit 1
fi
