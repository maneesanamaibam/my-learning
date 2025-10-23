$env:GOOS="js"
$env:ARCH="wasm"
go build -o main.wasm
