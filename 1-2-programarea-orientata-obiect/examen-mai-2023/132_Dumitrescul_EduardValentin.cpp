/*
 * Dumitrescul Eduard-Valentin 132
 * gcc (Clion implicit) - C++ 17
 * Profesor laborator: Szmeteanca Eduard
 */


#include <iostream>
#include <vector>
#include <map>

class IOInterface {
    virtual void read(std::istream& in) = 0;
    virtual void write(std::ostream& out) const = 0;
};

class Drum: IOInterface {
    std::string denumire;
    float lungime;
    int tronsoane;

public:

    virtual void read(std::istream& in);
    virtual void write(std::ostream& out) const;

    friend std::istream& operator >> (std::istream& in, Drum& object);
    friend std::ostream& operator << (std::ostream& out, const Drum& object);

    float lungimeTronson() const;
    std::string getDenumire() const { return this->denumire;}
    int getTronsoane() const { return this->tronsoane;}
    float getLungime() const{ return this->lungime;}
    virtual float cost() const = 0;

    virtual ~Drum();

};
std::istream& operator >> (std::istream& in, Drum& object) {
    object.read(in);
    return in;
}
std::ostream& operator << (std::ostream& out, const Drum& object) {
    object.write(out);
    return out;
}

void Drum::read(std::istream& in) {
    std::cout << "Denumire: ";
    in >> this->denumire;
    std::cout << "Lungime: ";
    in >> this->lungime;
    bool running = true;
    while(running) {
        std::cout << "Numar tronsoane: ";
        in >> this->tronsoane;
        if(this->tronsoane < 1) {
            std::cout << "Numarul trebuie sa fie cel puitn 1\n";
        }
        else {
            running = false;
        }
    }

}
void Drum::write(std::ostream& out) const {
    out << "* DRUM *\n";
    out << "Denumire: " << this->denumire << '\n';
    out << "Lungime: " << this->lungime << '\n';
    out << "Numar tronsoane: " << this->tronsoane << '\n';
}

float Drum::lungimeTronson() const{
    return (this->lungime / this->tronsoane);
}

Drum::~Drum() {}

class DrumNational: public Drum,  IOInterface {
    int judete;

public:
    float cost() const;
    void read(std::istream& in);
    void write(std::ostream& out) const;

};

void DrumNational::read(std::istream& in) {
    Drum::read(in);
    std::cout << "Nr judete: ";
    in >> this->judete;
}
void DrumNational::write(std::ostream& out) const {
    Drum::write(out);
    out << "Nr judete: " << this->judete << '\n';
}

float DrumNational::cost() const {
    return this->lungimeTronson() * 3000;
}

class DrumEuropean: virtual public Drum, IOInterface {
protected:
    int tari;
public:
    virtual float cost() const;
    virtual void read(std::istream& in);
    virtual void write(std::ostream& out) const;

    virtual ~DrumEuropean();
};

DrumEuropean::~DrumEuropean() {}

void DrumEuropean::read(std::istream& in) {
    Drum::read(in);
    std::cout << "Nr Tari: ";
    in >> this->tari;
}
void DrumEuropean::write(std::ostream& out) const {
    Drum::write(out);
   out << "Nr Tari: " << this->tari << '\n';
}

float DrumEuropean::cost() const {
    return this->lungimeTronson() * 3000 + 500 * this->tari;
}

class Autostrada: virtual public Drum, IOInterface {
    int benzi; //minim 2

public:
    virtual float cost() const;
    virtual void read(std::istream& in);
    virtual void write(std::ostream& out) const;

    virtual ~Autostrada();
};

Autostrada::~Autostrada() {};

void Autostrada::read(std::istream& in) {
    Drum::read(in);
    bool running = true;
    while(running) {
        try {
            std::cout << "Nr benzi: ";
            in >> this->benzi;
            if(this->benzi < 2) {
                throw this->benzi;
            }
            running = false;
        }
        catch (int ex) {
            std::cout << "Numarul de benzi trebuie sa fie cel putin 2 (valoarea ta: " << ex << ")";
        }
    }
}
void Autostrada::write(std::ostream& out) const {
    Drum::write(out);
    out << "Nr benzi: " << this->benzi << '\n';
}

float Autostrada::cost() const {
    return this->lungimeTronson() * 2500 * this->benzi;
}

class AutostradaEuro: public Autostrada, public DrumEuropean, IOInterface {
public:
    float cost() const;
    void read(std::istream& in);
    void write(std::ostream& out) const;
};

void AutostradaEuro::read(std::istream& in) {
    Autostrada::read(in);
    std::cout << "Nr Tari: ";
    in >> this->tari;
}
void AutostradaEuro::write(std::ostream& out) const {
    Autostrada::write(out);
    out << "Nr Tari: " << this->tari << '\n';
}

float AutostradaEuro::cost() const {
    return Autostrada::cost() + 500 * this->tari;
}



class Contract: IOInterface {
    static int idCount;
    const int id;
    std::string nume;
    std::string cod;
    Drum* drum;
    int tronson; // trebuie sa existe, un tronson un singur contract

public:
    Contract();
    Contract(const Contract& object);
    Contract& operator = (const Contract& object);

    friend std::istream& operator >> (std::istream& in, Contract& object);
    friend std::ostream& operator << (std::ostream& out, const Contract& object);

    void read(std::istream& in);
    void write(std::ostream& out) const;

    const Drum* getDrum() const { return this->drum;}
    int getTronson() const {return this->tronson;}

    bool operator == (std::string cif) {
        return this->cod == cif;
    };

    ~Contract();
};

int Contract::idCount = 0;

Contract::Contract(): id(++idCount) {
    this->nume = "nume";
    this->cod = "cod";
    this->drum = nullptr;
    this->tronson = 0;

}
Contract::Contract(const Contract& object): id(++idCount) {
    this->nume = object.nume;
    this->cod = object.cod;
    this->drum = object.drum;
    this->tronson = object.tronson;
}
Contract& Contract::operator = (const Contract& object){
    if(this != &object) {
        this->nume = object.nume;
        this->cod = object.cod;
        this->drum = object.drum;
        this->tronson = object.tronson;
    }
    return *this;
}

Contract::~Contract() {
    if(this->drum != nullptr) {
        delete this->drum;
    }
    this->drum = nullptr;
}

void Contract::read(std::istream& in) {
    std::cout << "Nume: ";
    in >> this->nume;
    std::cout << "Cod: ";
    in >> this->cod;

    if(this->drum != nullptr) {
        delete this->drum;
    }

    bool running = true;
    while(running) {
        std::cout << "[1] - Drum National\n";
        std::cout << "[2] - Drum European\n";
        std::cout << "[3] - Autostrada\n";
        std::cout << "[4] - Autostrada Europeana\n";


        int cmd;
        in >> cmd;
        try {
            switch (cmd) {
                case 1:{
                    this->drum = new DrumNational();
                    break;
                }
                case 2: {
                    this->drum = new DrumEuropean();
                    break;
                }
                case 3: {
                    this->drum = new Autostrada();
                    break;
                }
                case 4:{
                    this->drum = new AutostradaEuro();
                    break;
                }
                default: {
                    throw std::string ("Comanda inexistenta!");
                    break;
                }
            }

            running = false;
            in >> *this->drum;
        }
        catch (std::string ex) {
            std::cout << ex << '\n';
        }

    }

    running = true;
    while(running) {
        std::cout << "Tronson :";
        in >> this->tronson;
        if(1 <= this->tronson and this->tronson <= this->drum->getTronsoane()) {
            running = false;
        }
        else {
            std::cout << "Tronsonul nu exista!\n";
        }
    }


}
void Contract::write(std::ostream& out) const {
    out << "* CONTRACT " << this->id << " *\n";
    out << "Nume: " << this->nume << '\n';
    out << "Cod: " << this->cod << '\n';
    out << *this->drum;
    out << "Tronson: " << this->tronson << '\n';
}

std::istream& operator >> (std::istream& in, Contract& object) {
    object.read(in);
    return in;
}

std::ostream& operator << (std::ostream& out, const Contract& object) {
    object.write(out);
    return out;
}

        /// SINGLETON
class Meniu {

    static int instances;
    static Meniu* instance;

    std::map <std::pair <std::string, int>, bool> tronsonLuat;

    std::vector <Drum*> drumuri;
    std::vector <Contract*> contracte;

    Meniu() = default;
    Meniu(const Meniu& object) = delete;

public:
    static Meniu* getInstance();

    void run();
    void adaugaDrum();
    void afiseazaDrumuri();
    void adaugaContract();
    void afiseazaContracte();
    void calculeazaLungime();
    void stergeContracte();
    void costTotal();

    ~Meniu();
};


int Meniu::instances = 0;
Meniu* Meniu::instance = nullptr;

void Meniu::costTotal() {
    std::string nume;
    std::cout << "Denumire drum:";
    std::cin >> nume;
    float cost = 0;
    for(int i = 0; i < this->contracte.size(); i ++) {
        if(this->contracte[i]->getDrum()->getDenumire() == nume )
            cost += this->contracte[i]->getDrum()->cost();
    }
    std::cout << "Cost: " << cost << '\n';
}

Meniu* Meniu::getInstance(){
    if(instances == 0) {
        instance = new Meniu();
    }
    return instance;
}

Meniu::~Meniu() {
     instances --;
     if(instances == 0)
         delete instance;
 }

void Meniu::run() {
    bool running = true;
    while(running) {
        std::cout << "[0] - Exit\n";
        std::cout << "[1] - Adauga Drum\n";
        std::cout << "[2] - Afiseaza Toate Drumurile\n";
        std::cout << "[3] - Adauga Contract\n";
        std::cout << "[4] - Afiseaza toate contractele\n";
        std::cout << "[5] - Afiseaza lungime totala drumuri (respectiv a celor de tip autostrada)\n";
        std::cout << "[6] - Sterge Contrace dupa CIF\n";
        std::cout << "[7] - Cost Total Drum\n";

        int cmd;
        std::cin >> cmd;
        try {
            switch(cmd) {
                case 0: {
                    running = false;
                    break;
                }
                case 1: {
                    this->adaugaDrum();
                    break;
                }
                case 2: {
                    this->afiseazaDrumuri();
                    break;
                }
                case 3: {
                    this->adaugaContract();
                    break;
                }
                case 4: {
                    this->afiseazaContracte();
                    break;
                }
                case 5: {
                    this->calculeazaLungime();
                    break;
                }
                case 6: {
                    this->stergeContracte();
                    break;
                }
                case 7: {
                    this->costTotal();
                    break;
                }
                default: {
                    throw std::invalid_argument("comanda inexistenta");
                }
            }
        }
        catch (std::invalid_argument& ex) {
            std::cout << ex.what() << '\n';
            std::cout << "Mai incearca!\n";
        }

    }
}

void Meniu::stergeContracte() {
    std::string cif;
    std::cout <<"CIF: ";
    std::cin >> cif;
    std::vector <Contract*> temp;
    for(int i = 0; i < this->contracte.size(); i ++) {
        if(*this->contracte[i] == cif) {
            delete this->contracte[i];
        }
        else {
            temp.push_back(this->contracte[i]);
        }
    }
    this->contracte = temp;

}

void Meniu::calculeazaLungime() {
    float l=0, la=0;
    for(int i = 0; i < this->drumuri.size(); i ++) {
        if(dynamic_cast<Autostrada*>(this->drumuri[i])) {
            la += this->drumuri[i]->getLungime();
        }
        l += this->drumuri[i]->getLungime();
    }
    std::cout << "Lungime totala: " << l << '\n';
    std::cout << "Lungime autostrazi: " << la << '\n';
}

void Meniu::adaugaDrum() {
     Drum* temp;
    bool running = true;
    while(running) {
        std::cout << "[1] - Drum National\n";
        std::cout << "[2] - Drum European\n";
        std::cout << "[3] - Autostrada\n";
        std::cout << "[4] - Autostrada Europeana\n";


        int cmd;
        std::cin >> cmd;
        try {
            switch (cmd) {
                case 1:{
                    temp = new DrumNational();
                    break;
                }
                case 2: {
                    temp = new DrumEuropean();
                    break;
                }
                case 3: {
                    temp = new Autostrada();
                    break;
                }
                case 4:{
                    temp = new AutostradaEuro();
                    break;
                }
                default: {
                    throw std::string ("Comanda inexistenta!");
                    break;
                }
            }

            running = false;
            std::cin >> *temp;
            this->drumuri.push_back(temp);
        }
        catch (std::string ex) {
            std::cout << ex << '\n';
        }

    }
    std::cout << "Drum Adaugat\n";
}

void Meniu::afiseazaDrumuri() {
    for(int i = 0; i < this->drumuri.size(); i ++) {
        std::cout << *this->drumuri[i] << '\n';
    }
}

void Meniu::adaugaContract() {
    Contract *temp = new Contract();
    bool running = true;
    while(running) {
        try {
            std::cin >> *temp;
            if(tronsonLuat[{temp->getDrum()->getDenumire(), temp->getTronson()}])
                throw std::invalid_argument("Tronsonul pentru drumul respectiv face parte dintr-un contract");
            tronsonLuat[{temp->getDrum()->getDenumire(), temp->getTronson()}] = true;
            this->contracte.push_back(temp);
            running = false;
        }
        catch (std::invalid_argument& ex) {
            std::cout << ex.what() << '\n';
        }
    }
    std::cout << "Contract Adaugat\n";

}

void Meniu::afiseazaContracte() {
    for(int i = 0; i < this->contracte.size(); i ++) {
        std::cout << *this->contracte[i] << '\n';
    }
}

int main() {
    Meniu *meniu = Meniu::getInstance();

    meniu->run();

    delete meniu;
    return 0;
}
