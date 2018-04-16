cd $PSScriptRoot
$branch ="4.19"
$repo = "UE4-DynamicalSystems"




Function Execute-Command ($commandTitle, $commandPath, $commandArguments)
{
    $pinfo = New-Object System.Diagnostics.ProcessStartInfo
    $pinfo.FileName = $commandPath
    $pinfo.RedirectStandardError = $true
    $pinfo.RedirectStandardOutput = $true
    $pinfo.UseShellExecute = $false
    $pinfo.Arguments = $commandArguments
    $p = New-Object System.Diagnostics.Process
    $p.StartInfo = $pinfo
    $p.Start() | Out-Null
    $stdout = $p.StandardOutput.ReadToEnd()
    $stderr = $p.StandardError.ReadToEnd()
    $p.WaitForExit()
    Write-Host "stdout: $stdout"
    Write-Host "stderr: $stderr"
    Write-Host "exit code: " + $p.ExitCode
}


$cmd = "git.exe"
$args = "init"

Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args

$args = " remote add origin git@github.com:RedPillVR/$repo"
Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args

$args = "fetch "
Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args


$args = "checkout origin/$branch  . "
Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args
$args = " pull origin $branch "
Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args

$args = " branch -d $branch"
Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args

$args = " checkout -b $branch"
Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args
$args = "checkout origin/$branch  . "
Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args
$args = " lfs pull"
Execute-Command -commandTitle "7z" -commandPath $cmd -commandArguments $args

