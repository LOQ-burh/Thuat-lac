#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct QNode {
	int data;
	QNode* next;

	QNode()
	{
		next = NULL;
	}
	QNode(int d)
	{
		data = d;
		next = NULL;
	}
	void input() {
		cout << "data: ";
		cin >> this->data;
	}
};

struct NhaTro {
	string maPhong;
	string hoTen;
	string ngaySinh; // Định dạng DD/MM/YYYY
	string soCMND;
	int chiSoDien;
	int chiSoNuoc;
	double donGia;

	NhaTro* next;
	NhaTro()
	{
		// cout << "ham khoi tao duoc goi!\n";
		this->maPhong = this->hoTen = this->ngaySinh = this->soCMND = "";
		this->chiSoDien = this->chiSoNuoc = 0;
		this->donGia = 0;
		next = NULL;
	}
	NhaTro(string maPhong, string hoTen, string ngaySinh, string soCMND, int chiSoDien, int chiSoNuoc, double donGia)
	{
		this->maPhong = maPhong;
		this->hoTen = hoTen;
		this->ngaySinh = ngaySinh;
		this->soCMND = soCMND;
		this->chiSoDien = chiSoDien;
		this->chiSoNuoc = chiSoNuoc;
		this->donGia = donGia;
		next = NULL;
	}
	void input() {
		cout << "nhap ma phong tro: ";
		cin >> this->maPhong;
		cin.ignore();
		cout << "nhap ho ten nguoi thue tro: ";
		getline(cin, this->hoTen);
		cout << "nhap ngay thang nam sinh: ";
		cin >> this->ngaySinh;
		cout << "nhap chi so dien: ";
		cin >> this->chiSoDien;
		cout << "nhap chi so nuoc: ";
		cin >> this->chiSoNuoc;
		cout << "nhap don gia phong tro: ";
		cin >> this->donGia;
		cout << endl;
	}
	void toString() {
		cout << "id: " << this->maPhong << endl;
		cout << "ten: " << this->hoTen << endl;
		cout << "ngay sinh: " << this->ngaySinh << endl;
		cout << "chi so dien: " << this->chiSoDien << endl;
		cout << "chi so nuoc: " << this->chiSoNuoc << endl;
		cout << "don gia: " << fixed << setprecision(2) << this->donGia << endl;
	}

};

class Queue {

	NhaTro nhaTro;

public:
	NhaTro* front, * rear;

public:
	Queue() {
		front = NULL;
		rear = NULL;
	}

	void enqueue(string maPhong,
		string hoTen,
		string ngaySinh,
		string soCMND,
		int chiSoDien,
		int chiSoNuoc,
		double donGia) {
		NhaTro* temp = new NhaTro(maPhong, hoTen, ngaySinh, soCMND, chiSoDien, chiSoNuoc, donGia);
		if (rear == NULL) {
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp;
	}

	//Xóa 1 phòng trọ trong Queue.
	void dequeue() {
		if (front == NULL) { return; }
		NhaTro* temp = front;
		front = front->next;

		if (front == NULL) {
			rear = NULL;
		}

		delete (temp);
	}

	void display() {
		NhaTro* current = front;
		while (current != NULL) {
			std::cout << "Ma Phong: " << current->maPhong << endl <<
				"Ho Ten: " << current->hoTen << endl <<
				"Ngay sinh: " << current->ngaySinh << endl <<
				"Chi so dien: " << current->chiSoDien << endl <<
				"Chi so nuoc: " << current->chiSoNuoc << endl <<
				"Don gia: " << current->donGia << "\n\n";
			current = current->next;
		}
	}
	// Hàm tìm kiếm nhà trọ có chi số điện cao nhất
	NhaTro* timChiSoDienCaoNhat() {
		if (front == NULL) {
			return NULL;
		}

		NhaTro* maxChiSoDienNhaTro = front;
		NhaTro* current = front->next;

		while (current != NULL) {
			if (current->chiSoDien > maxChiSoDienNhaTro->chiSoDien) {
				maxChiSoDienNhaTro = current;
			}
			current = current->next;
		}

		return maxChiSoDienNhaTro;
	}
	// Hàm tìm kiếm nhà trọ theo tên người thuê
	NhaTro* timNhaTroTheoTen(const std::string& hoTen) {
		NhaTro* current = front;
		while (current != NULL) {
			if (current->hoTen == hoTen) {
				return current;
			}
			current = current->next;
		}
		return NULL;
	}
	// Hàm Đếm số phòng trọ có đơn giá phòng trọ cao nhất. 
	int timSoPhongTroCoDonGiaCaoNhat() {
		if (front == NULL) {
			return 0;
		}
		int count = 0;
		NhaTro* maxDonGia = front;
		NhaTro* current = front->next;

		while (current != NULL) {
			if (current->chiSoDien > maxDonGia->chiSoDien) {
				maxDonGia = current;
				count++;
			}
			current = current->next;
		}

		return count;
	}

	// Hàm tính tổng chỉ số điện
	int tinhTongChiSoDien() {
		int tongChiSoDien = 0;
		NhaTro* current = front;
		while (current != NULL) {
			tongChiSoDien += current->chiSoDien;
			current = current->next;
		}
		return tongChiSoDien;
	}

	// Hàm đếm số lượng phòng trọ có người thuê trọ sinh trước năm 2002
	int demSoPhongTroNguoiThueSinhtuNam(int nam) {
		int dem = 0;
		NhaTro* current = front;
		while (current != NULL) {
			string namSinh = current->ngaySinh.substr(6, 4);
			int namInt = std::stoi(namSinh);
			if (namInt < nam) {
				dem++;
			}
			current = current->next;
		}
		return dem;
	}

	// Hàm đọc file với tên file đầu vào và trả về danh sách nhà trọ
	void docFileDanhSachNhaTro(const string& tenFile, vector<NhaTro> dsNhaTro) {
		ifstream infile;
		infile.open(tenFile);

		string line;

		if (infile.is_open()) {
			while (getline(infile, line)) {
				std::istringstream iss(line);
				NhaTro nhaTro;
				string maPhong, hoTen, ngaySinh;
				int soCMND, chiSoDien, chiSoNuoc;
				double donGia;

				getline(iss, nhaTro.maPhong, '\n');
				getline(iss, nhaTro.hoTen, '\n');
				getline(iss, nhaTro.ngaySinh, '\n');
				infile >> nhaTro.soCMND; cout << endl;
				infile >> nhaTro.chiSoDien; cout << endl;
				infile >> nhaTro.chiSoNuoc; cout << endl;
				infile >> nhaTro.donGia; cout << endl;

				// Thêm vào danh sách nhà trọ
				dsNhaTro.push_back(nhaTro);
			}
			infile.close();
		}
		else {
			cerr << "Khong the mo file: " << tenFile << endl;
		}
	}

	// Hàm ghi danh sách nhà trọ vào file output.txt
	void ghiFileDanhSachNhaTro(const vector<NhaTro>& dsNhaTro, const string& tenFile) {
		ofstream outFile(tenFile);

		if (outFile.is_open()) {
			for (const auto& nhaTro : dsNhaTro) {
				outFile << nhaTro.maPhong << endl <<
					nhaTro.hoTen << endl <<
					nhaTro.ngaySinh << endl <<
					nhaTro.soCMND << endl <<
					nhaTro.chiSoDien << endl <<
					nhaTro.chiSoNuoc << endl <<
					nhaTro.donGia << endl;
			}
			outFile.close();
		}
		else {
			std::cerr << "Khong the tao file: " << tenFile << std::endl;
		}
	}
};



int main()
{
	Queue hangDoiNhaTro;

	hangDoiNhaTro.enqueue("P001", "Tran Van A", "01/01/1990", "123456789", 100, 150, 3000.5);
	hangDoiNhaTro.enqueue("P002", "Nguyen Van b", "01/01/1990", "123456789", 100, 150, 3000.5);

	cout << "Thong tin nhung nha tro trong queue: \n";
	hangDoiNhaTro.display();

	// Xóa phần tử khỏi hàng đợi sau khi xử lý xong
	hangDoiNhaTro.dequeue();

	// Hiển thị lại hàng đợi sau khi một nhà trọ được xóa
	cout << "\nSau khi dequeue:\n";
	hangDoiNhaTro.display();

	NhaTro* nhaTroCoChiSoDienCaoNhat = hangDoiNhaTro.timChiSoDienCaoNhat();
	if (nhaTroCoChiSoDienCaoNhat != nullptr) {
		cout << "Phong tro co chi so dien cao nhat:\n";
		cout << "Ma Phong: " << nhaTroCoChiSoDienCaoNhat->maPhong << endl <<
			"Chi So Dien: " << nhaTroCoChiSoDienCaoNhat->chiSoDien << "\n";
	}
	else {
		cout << "Queue khong co nha tro nao.\n";
	}

	std::string tenCanTim = "Tran Van A";
	NhaTro* nhaTroCuaTranVanA = hangDoiNhaTro.timNhaTroTheoTen(tenCanTim);
	if (nhaTroCuaTranVanA != NULL) {
		cout << "Thong tin nha tro cua " << tenCanTim << "\n";
		cout << "Ma Phong: " << nhaTroCuaTranVanA->maPhong << "\n";
		// In ra thông tin khác của phòng trọ nếu muốn
	}
	else {
		cout << "Khong tim thay nha tro cua " << tenCanTim << "\n";
	}

	int soPhongTroDonGiaCaoNhat = hangDoiNhaTro.timSoPhongTroCoDonGiaCaoNhat();
	if (soPhongTroDonGiaCaoNhat != 0) {
		cout << "So phong tro co don gia cao nhat" << soPhongTroDonGiaCaoNhat << "\n";
	}
	else {
		cout << "Khong co so phong tro nao co don gia cao nhat" << "\n";
	}

	int tongChiSoDien = hangDoiNhaTro.tinhTongChiSoDien();
	cout << "Tong chi so dien cua tat ca phong tro la: " << tongChiSoDien << "\n";

	int soLuongPhongTro = hangDoiNhaTro.demSoPhongTroNguoiThueSinhtuNam(2002);
	std::cout << "So luong phong tro co nguoi thue sinh truoc nam 2002 la: " << soLuongPhongTro << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
