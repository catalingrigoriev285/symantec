$buildFolderPath = "build"

if (-not (Test-Path -Path $buildFolderPath)) {
    New-Item -ItemType Directory -Path $buildFolderPath -Force | Out-Null
}

Push-Location -Path $buildFolderPath
try {
    cmake ../
    cmake --build . --config Release
} finally {
    Pop-Location
}
