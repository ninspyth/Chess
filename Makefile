default:
	g++ main.cpp -o main -I"C:\raylib\include" -L"C:\raylib\lib" -lraylib -lgdi32 -lopengl32 -lwinmm

clean:
	rm -f main
