#include <string>
#include <iostream>
#include <vector>

int main()
{
	std::string sv1_1 = "kissa";

	std::string sv1_2 = "";

	std::string sv2_1 = "kissa";
	std::string sv2_2 = "";

	//a)
	/*Sijoita s1:n arvoksi s2. Tutki debuggerilla tilannetta ennen tai j�lkeen sijoituksen. Yrit� l�yt��
	std::string-olioiden sis�lt� osoitin varsinaiseen merkkijonodataan. Mit� huomaat?*/

	sv1_1 = sv1_2;  //eli 1:n arvoksi tulee sama arvo kuin 2:lla eli tyhj�..
	sv2_2 = sv2_1;	//tyhj� merkkijono saa kissa-merkkijonon..

	std::cout <<"a) "<<sv1_1 << ":" << sv1_2 << ":" << sv2_1 << ":" << sv2_2 << "\n";

	
	/*b) Sijoita s1:n arvoksi s2, mutta muuta s2 ensin rvalue-referenssiksi (std::move). Tutki debuggerilla
tilannetta ennen tai j�lkeen sijoituksen. Yrit� l�yt�� std::string-olioiden sis�lt� osoitin varsinaiseen
merkkijonodataan. Mit� huomaat?*/

	std::string sv3_1 = "kissa";

	std::string sv3_2 = "";

	std::string sv4_1 = "kissa";
	std::string sv4_2 = "";

	sv3_2 = std::move(sv3_2);

	sv4_2 = std::move(sv4_1);



	/*
	c) Luo viel� merkkijonovektori (std::vector). Lis�� luo std::string s3, jonka arvona on �koira�. Lis��
	s3 vektoriin (push_back) normaalisti, ja vaihtoehtoisesti muuttamalla s3 ensin rvaluereferenssiksi
	(std::move). Tutki sijoituksia debuggerilla. Mit� huomaat?*/

	std::vector<std::string> merkkijonot;
	std::string s31 = "koira";
	std::string s32 = "koira2";
	merkkijonot.push_back(s31);
	merkkijonot.push_back(std::move(s32));



	std::cout << "done\n";
	std::cout << "done2\n";
	return 0;
}