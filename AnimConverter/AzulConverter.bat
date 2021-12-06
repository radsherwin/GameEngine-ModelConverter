@ECHO OFF

del /q .\Output\*
for /d %%x in (.\Output\*) do @rd /s /q "%%x"

.\Debug\SandBox.exe -i walk_mesh.glb -o .\Output\walk_mesh
.\Debug\SandBox.exe -a die_left_mesh.glb -o .\Output\die_left_mesh
.\Debug\SandBox.exe -a shot_down_mesh.glb -o .\Output\shot_down_mesh
.\Debug\SandBox.exe -a hit_right_mesh.glb -o .\Output\hit_right_mesh
.\Debug\SandBox.exe -a run_RM_mesh.glb -o .\Output\run_RM_mesh
.\Debug\SandBox.exe -t ChickenbotDiffuse.png -o .\Output\ChickenbotDiffuse


ECHO Output file: .\Output\ 