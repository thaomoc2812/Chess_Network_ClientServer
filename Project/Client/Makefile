client: client.o home.o quanco.o banco.o include.o menu.o clickChuot.o dangnhap.o dangky.o dsonl.o
	g++ -o client client.o home.o quanco.o banco.o include.o menu.o  clickChuot.o dangnhap.o dangky.o dsonl.o -lSDL2 -lSDL2_image -lSDL2_ttf
client.o: client.cpp Home/home.hpp
	g++ -c client.cpp 
home.o: Home/home.cpp Home/home.hpp QuanCo/quanco.hpp BanCo/banco.hpp Menu/menu.hpp ClickChuot/clickChuot.hpp DangNhap/dangnhap.hpp DangKy/dangky.hpp DanhSachOnl/dsonl.hpp
	g++ -c Home/home.cpp 


quanco.o: QuanCo/quanco.cpp QuanCo/quanco.hpp Include/include.hpp
	g++ -c QuanCo/quanco.cpp

banco.o: BanCo/banco.cpp BanCo/banco.hpp Include/include.hpp
	g++ -c BanCo/banco.cpp

include.o: Include/include.cpp Include/include.hpp
	g++ -c Include/Include/include.cpp

menu.o: Menu/menu.cpp Menu/menu.hpp
	g++ -c Menu/menu.cpp

clickChuot.o: ClickChuot/clickChuot.cpp ClickChuot/clickChuot.hpp
	g++ -c ClickChuot/clickChuot.cpp

dangnhap.o: DangNhap/dangnhap.cpp DangNhap/dangnhap.hpp
	g++ -c DangNhap/dangnhap.cpp

dangky.o: DangKy/dangky.cpp DangKy/dangky.hpp
	g++ -c DangKy/dangky.cpp

dsonl.o: DanhSachOnl/dsonl.cpp DanhSachOnl/dsonl.hpp
	g++ -c DanhSachOnl/dsonl.cpp