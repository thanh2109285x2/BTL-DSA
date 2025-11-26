#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm> 

using namespace std;

class SinhVien {
private:
	string MaSV;
	string HoTen;
	int Tuoi;
	float Diem;
public:
	friend istream& operator >> (istream &cin, SinhVien &sv);
	friend ostream& operator << (ostream &cout, const SinhVien &sv);
	bool operator < (const SinhVien &other) const;
    string getMaSV() const { return MaSV; }
    string getHoTen() const { return HoTen; }
    int getTuoi() const { return Tuoi; }
    float getDiem() const { return Diem; }
};

istream& operator >> (istream &cin, SinhVien &sv){
	cout <<"Nhap ma sinh vien:";
	cin.ignore() ;getline(cin, sv.MaSV);
	cout <<"\n" ;
	cout <<"Nhap ho va ten:";
	getline(cin, sv.HoTen);
	cout <<"\n" ;
	cout << "Nhap tuoi:";
	cin >> sv.Tuoi;
	cout <<"\n" ;
	cout << "Nhap diem:";
	cin >> sv.Diem;
	cout <<"\n" ;
	return cin;
}

ostream& operator << (ostream& cout,const SinhVien& sv){
	auto now = chrono::system_clock::now();
	time_t curr_time = chrono::system_clock::to_time_t(now);
	tm* local_time = localtime(&curr_time);
	int year = 1900 + local_time->tm_year;
	cout << "Ma sinh vien:" << sv.MaSV << ", " << "Ho va ten:" << sv.HoTen << ", " << "Tuoi:" << sv.Tuoi << ", " <<
			"Nam sinh:" << year - sv.Tuoi << ", " << "Diem hoc ki:" << sv.Diem << endl;
	return cout;
}

bool SinhVien::operator < (const SinhVien &other) const{
	return Diem < other.Diem;
}

class DanhSach{
private:
	vector<SinhVien> DanhSach;
	int n;
public:
	void HamNhap(){
		cout<<"nhap so luong sinh vien: ";
		cin >> n;
		cout << "\n";
		while(n <= 0) {
			cout << "nhap nhieu hon 1 sinh vien: ";
			cin >> n;
			cout << "\n";
		}
		DanhSach.resize(n);
		for(int i = 0; i < n; i++){
			cin >> DanhSach[i];
		}
	}	
	void HamXuat(){
		for(int i = 0; i < n; i++){
			cout << DanhSach[i];
		}
		cout << "\n";
	}
	void SapXep(){
		cout << "Chon phuong an sap xep sinh vien:\n"
			<<	"1.Sap xep theo ma sinh vien\n"
			<<	"2.Sap xep theo chu cai dau cua ho ten\n"
			<<	"3.Sap xep theo tuoi\n"
			<<	"4.Sap xep theo diem\n";
		int a;
		cout << "Chon phuong an:";
		cin >> a;
		cout << "\n";
		switch (a){
			case 1:
				sort(DanhSach.begin(), DanhSach.end(), [](const SinhVien &a, const SinhVien &b){
					return a.getMaSV() < b.getMaSV();
				});
				break;
			case 2:
				sort(DanhSach.begin(), DanhSach.end(), [](const SinhVien &a, const SinhVien &b){
					return a.getHoTen() < b.getHoTen();
				});
				break;
			case 3:
				sort(DanhSach.begin(), DanhSach.end(), [](const SinhVien &a, const SinhVien &b){
					return a.getTuoi() < b.getTuoi();
				});
				break;
			case 4:
				sort(DanhSach.begin(), DanhSach.end(), [](const SinhVien &a, const SinhVien &b){
					return a.getDiem() < b.getDiem();
				});
				break;
			default:
	            cout << "Lua chon khong hop le!\n";
	            return;
		}
	}
	void TimMax() {
	    cout << "Chon phuong an tim sinh vien: " << "\n"
	         << "1. Tim tat ca sinh vien co tuoi lon nhat\n"
	         << "2. Tim tat ca sinh vien co diem cao nhat\n";
	    int a;
	    cout << "Chon phuong an: ";
	    cin >> a;
	    cout << "\n";
	
	    if (DanhSach.empty()) {
	        cout << "Danh sach trong!\n";
	        return;
	    }
	
	    vector<int> LuuTru;
	
	    switch (a) {
	        case 1: {
	            int maxTuoi = DanhSach[0].getTuoi();
	            for (int i = 1; i < DanhSach.size(); i++) {
	                if (DanhSach[i].getTuoi() > maxTuoi)
	                    maxTuoi = DanhSach[i].getTuoi();
	            }
	            for (int i = 0; i < DanhSach.size(); i++) {
	                if (DanhSach[i].getTuoi() == maxTuoi)
	                    LuuTru.push_back(i);
	            }
	            cout << "Sinh vien co tuoi lon nhat (" << maxTuoi << " tuoi):\n";
	            break;
	        }
	
	        case 2: {
	            float maxDiem = DanhSach[0].getDiem();
	            for (int i = 1; i < DanhSach.size(); i++) {
	                if (DanhSach[i].getDiem() > maxDiem)
	                    maxDiem = DanhSach[i].getDiem();
	            }
	            for (int i = 0; i < DanhSach.size(); i++) {
	                if (DanhSach[i].getDiem() == maxDiem)
	                    LuuTru.push_back(i);
	            }
	            cout << "Sinh vien co diem cao nhat (" << maxDiem << "):\n";
	            break;
	        }
	
	        default:
	            cout << "Lua chon khong hop le!\n";
	            return;
	    }
	    
	    if (LuuTru.empty()) {
	        cout << "Khong tim thay sinh vien phu hop.\n";
	    } else {
	        for (int idx : LuuTru) {
	            cout << DanhSach[idx];
	        }
	    }
	    cout << "\n";
	}

	void TimKiem(){
		int a;
		vector<int> LuuTru;
		cout << "Chon phuong an sap xep sinh vien: "<< "\n" <<
				"1.Tim kiem theo ma sinh vien" << "\n" <<
				"2.Tim kiem theo ho ten" << "\n" <<
				"3.Tim kiem theo tuoi"  << "\n" <<
				"4.Tim kiem theo diem"  << "\n";
		cout << "Chon phuong an:";
		cin >> a;
		cout << "\n";
		switch (a){
			case 1:{
				string s;
				cout << "Nhap ma sinh vien can tim: ";
				cin.ignore(); getline(cin, s);
				cout <<"\n";
				for(int i = 0 ; i < n; i++){
					if(DanhSach[i].getMaSV() == s){
						LuuTru.push_back(i);
					}
				}
				break;
			}
			case 2:{
				string s;
				cout << "Nhap ho va ten sinh vien can tim: ";
				cin.ignore(); getline(cin, s);
				cout <<"\n";
				for(int i = 0 ; i < n; i++){
					if(DanhSach[i].getHoTen() == s){
						LuuTru.push_back(i);
					}
				}
				break;
			}
			case 3:{
				int x;
				cout << "Nhap tuoi can tim: ";
				cin >> x;
				cout <<"\n";
				for(int i = 0 ; i < n; i++){
					if(DanhSach[i].getTuoi() == x){
						LuuTru.push_back(i);
					}
				}
				break;
			}
			case 4:{
				float x;
				cout << "Nhap diem sinh vien can tim: ";
				cin >> x;
				cout <<"\n";
				for(int i = 0 ; i < n; i++){
					if(DanhSach[i].getDiem() == x){
						LuuTru.push_back(i);
					}
				}
				break;
			}
			default:
	            cout << "Lua chon khong hop le!\n";
	            return;	
		}
		if(LuuTru.empty()) {
		    cout << "Khong tim thay sinh vien phu hop.\n";
		} 
		else {
		    cout << "Cac sinh vien tim thay:\n";
		    for(int idx : LuuTru) {
		        cout << DanhSach[idx];
		    }
		}
	}
};

class App {
private:
    DanhSach ds;
public:
    void Menu() {
        int chon;
        do{
            cout << "=========== MENU ===========\n"
				<<	"1. Nhap danh sach sinh vien\n"
				<<	"2. Xuat danh sach sinh vien\n"
				<<	"3. Sap xep danh sach\n"
				<<	"4. Tim sinh vien co diem hoac nam sinh lon nhat \n"
				<<	"5. Tim sinh vien theo lua chon"
				<<	"0. Thoat\n"
					<< "============================\n";
            cout << "Nhap lua chon: ";
            cin >> chon;
            
            switch(chon) {
                case 1:
                    ds.HamNhap();
                    break;
                case 2:
                    ds.HamXuat();
                    break;
                case 3:
                    ds.SapXep();
                    break;
                case 4:
                    ds.TimMax();
                    break;
                case 5:
                	ds.TimKiem();
                	break;
                case 0:
                    cout << "Thoat chuong trinh...\n";
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
            }
        }while(chon != 0);
    }
};

int main(){
	App app;
	app.Menu();
	return 0;
} 
