# Check argument
if ($args.Length -lt 2)
{
    return -1
}

$dstpath = $args[0]
$srcpath = $args[1]

# Extract
Expand-Archive -Path $srcpath -DestinationPath $dstpath -Force
