import random

first_names = ['Ethan', 'Isaac', 'Leo', 'Miles', 'Asher',
               'Maxwell', 'Oscar', 'Dylan', 'Oliver', 'Harrison',
               'Nathan', 'Gabriel', 'Jasper', 'Ezra', 'Silas',
               'Sebastian', 'Caleb', 'Gideon', 'Wyatt', 'Finn']
last_names = ['Garcia', 'Lee', 'Chen', 'Ali', 'Nguyen',
              'Patel', 'Smith', 'Wong', 'Gonzalez', 'Brown',
              'Khan', 'Singh', 'Lopez', 'Hernandez', 'Kim',
              'Wilson', 'Davis', 'Taylor', 'Anderson', 'Thomas']
team_names = ['Lightning Bolts', 'Thunderbirds', 'Wildcats', 'Heatwave',
              'Hurricanes', 'Jaguars', 'Patriots', 'Titans',
              'Vikings', 'Dragons', 'Raptors', 'Warriors',
              'Hornets', 'Sharks', 'Lions', 'Knights']
arena_names = ['The Thunderdome', 'The Coliseum', 'The Pit', 'The Garden',
               'The Staples Center', 'The Oracle', 'The Hoop House', 'The Den',
               'The Arena', 'The Thunderdome', 'The Dome', 'The Palace',
               'The Madhouse', 'The Pavilion', 'The Buzzer Beater', 'The Swish Center']
awards = ['Most Valuable Player (MVP)', 'Rookie of the Year',
          'Defensive Player of the Year', 'Sixth Man of the Year', 'Most Improved Player']
locations = [
    ('USA', 'New York City', 'Fifth Avenue', 742),
    ('USA', 'Los Angeles', 'Hollywood Boulevard', 6801),
    ('USA', 'Las Vegas', 'Las Vegas Boulevard', 3570),
    ('USA', 'Chicago', 'Michigan Avenue', 875),
    ('USA', 'San Francisco', 'Lombard Street', 1099),
    ('USA', 'Miami', 'Ocean Drive', 100),
    ('USA', 'Orlando', 'International Drive', 8000),
    ('USA', 'Houston', 'NASA Road 1', 1601),
    ('USA', 'Seattle', 'Pike Place Market', 85),
    ('USA', 'Washington D.C.', '1600 Pennsylvania Avenue NW', 1600),
    ('USA', 'Boston', 'Fenway Park', 4),
    ('USA', 'Atlanta', 'Peachtree Street', 303),
    ('USA', 'Dallas', 'Dealey Plaza', 411),
    ('USA', 'Denver', '16th Street Mall', 1001),
    ('USA', 'New Orleans', 'Bourbon Street', 500),
    ('USA', 'San Diego', 'Balboa Park', 1549)
]


def getDate(day, month, year):
    dstr = str(day)
    if day < 10:
        dstr = "0" + dstr
    mstr = str(month)
    if month < 10:
        mstr = "0" + mstr
    ystr = str(year)
    if year < 1000:
        ystr = "0" + ystr
    string = f"to_date('{dstr}-{mstr}-{ystr}', 'DD-MM-YYYY')"
    return string

nr_sezoane = 5
def insertSezoane():
    with open("insert-sezoane.txt", 'w') as f:
        for i in range(nr_sezoane):
            data_start = getDate(15, 8, 2023 - i)
            data_final = getDate(10, 6, 2024 - i)
            query = f"insert into sezoane values(idseq.nextval, {data_start}, {data_final});"
            print(query, file=f)

id_sezon = 1000
nr_etape = 30

def insertEtape():
    with open("insert-etape.txt", 'w') as f:
        for i in range(nr_etape):
            query = f"insert into etape values(idseq.nextval, {id_sezon}, {i+1});"
            print(query, file=f)

id_etapa = 1005
nr_angajati = 48

def insertAngajati():
    with open('insert-angajati.txt', 'w') as f:
        for i in range(nr_angajati):
            nume = last_names[random.randint(0, 19)]
            prenume = first_names[random.randint(0, 19)]
            salary = str(random.randint(100, 200) * 100)
            query = f"insert into angajati values(idseq.nextval, '{nume}', '{prenume}', {salary});"
            print(query, file=f)

id_angajat = 1035
nr_antrenori = 16

def insertAntrenori():
    with open('insert-antrenori.txt', 'w') as f:
        for id in range(id_angajat, id_angajat + 16):
            query = f"insert into antrenori values({id});"
            print(query, file=f)
id_antrenor = 1035

nr_preparatori = 16
id_preparator = 1051
def insertPreparatoriFizici():
    with open('insert-preparatori.txt', 'w') as f:
        for id in range(id_angajat + 16, id_angajat + 32):
            query = f"insert into preparatori_fizici values({id});"
            print(query, file=f)

nr_nutritionisti = 16
def insertNutritionisti():
    with open('insert-nutritionisti.txt', 'w') as f:
        for id in range(id_angajat + 32, id_angajat + 48):
            query = f"insert into nutritionisti values({id});"
            print(query, file=f)

id_nutritionist = 1067

nr_locatii = 16
id_locatie = 1083
def insertLocatii():
    with open('insert-locatii.txt', 'w') as f:
        for i in range (nr_locatii):
            tara = locations[i][0]
            oras = locations[i][1]
            strada = locations[i][2]
            nr = locations[i][3]
            query = f"insert into locatii values(idseq.nextval, '{tara}', '{oras}', '{strada}', '{nr}');"
            print(query, file=f)

nr_arene = 16
id_arena = 1099
def insertArene():
    with open('insert-arene.txt', 'w') as f:
        for i in range(nr_arene):
            nume = arena_names[i]
            locuri = random.randint(20, 40) * 1000
            query = f"insert into arene values(idseq.nextval, {id_locatie + i}, '{nume}', {locuri});"
            print(query, file=f)

nr_echipe = 16
id_echipa = 1115
def insertEchipe():
    with open('insert-echipe.txt', 'w') as f:
        for i in range(nr_echipe):
            nume = team_names[i]
            an = random.randint(1970, 2010)
            query = f"insert into echipe values(idseq.nextval, {id_arena+i}, {id_antrenor+i}, {id_preparator+i}" \
                    f",{id_nutritionist+i}, '{nume}', {an});"
            print(query, file=f)

nr_jucatori_ech = 5
id_jucator = 1131
def insertJucatori():
    with open('insert-jucatori.txt', 'w') as f:
        for ech in range(nr_echipe):
            for i in range(nr_jucatori_ech):
                nume = last_names[random.randint(0, 19)]
                prenume = first_names[random.randint(0, 19)]
                h = 1.8 + random.random() * 0.4
                inaltime = round(h, 2)
                salariu = random.randint(30, 50) * 1000
                query = f"insert into jucatori values(idseq.nextval, {id_echipa + ech}, '{nume}', '{prenume}', {inaltime}, {salariu});"
                print(query, file=f)

nr_echipe_med = 5
id_echipe_med = 1211
def insertEchipeMedicale():
    with open('insert-med.txt', 'w') as f:
        for i in range (nr_echipe_med):
            query = f"insert into echipe_medicale values(idseq.nextval);"
            print(query, file=f)

nr_meciuri = 240
id_meci = 1216

def insertMeciuri():
    with open('insert-meciuri.txt', 'w') as f:
        arr = [[i for i in range(8)], [(15-i) for i in range(8)]]
        reverse = False

        for nret in range(30):
            for i in range(8):
                home = id_echipa + arr[0][i]
                away = id_echipa + arr[1][i]
                med = id_echipe_med + random.randint(0, nr_echipe_med-1)
                if reverse == True:
                    home, away = away, home
                score_home = random.randint(50, 120)
                score_away = random.randint(50, 120)
                while score_away == score_home:
                    score_away = random.randint(50, 120)

                query = f"insert into meciuri values(idseq.nextval, {id_etapa + nret}, {home}, {away}, {med}, {score_home}, {score_away});"
                print(query, file=f)

            temp = arr[1][0]
            for i in range(7):
                arr[1][i] = arr[1][i+1]
            arr[1][7] = arr[0][7]
            for i in range(7, 1, -1):
                arr[0][i] = arr[0][i-1]
            arr[0][1] = temp

            if arr[0][1] == 2:
                reverse = True


nr_arbitrii = 5
id_arbitru = 1456
def insertArbitrii():
    with open('insert-arbitrii.txt', 'w') as f:
        for i in range(nr_arbitrii):
            nume = last_names[random.randint(0, 19)]
            prenume = first_names[random.randint(0, 19)]
            obt = getDate(random.randint(1, 28), random.randint(1, 12), random.randint(1970, 2000))
            query = f"insert into arbitrii values(idseq.nextval, '{nume}', '{prenume}', {obt});"
            print(query, file=f)

nr_comentatori = 5
id_comentator = 1461
def insertComentatori():
    with open('insert-comentatori.txt', 'w') as f:
        for i in range(nr_comentatori):
            nume = last_names[random.randint(0, 19)]
            prenume = first_names[random.randint(0, 19)]
            query = f"insert into comentatori values(idseq.nextval, '{nume}', '{prenume}');"
            print(query, file=f)


nr_statistici = 10
id_statistica = 1466
def insertStatistici():
    with open('insert-statistici.txt', 'w') as f:
        idmeci = 1216 #primul meci
        idhome = 1115
        idaway = 1130
        idhome_player = 1131
        idaway_player = 1206

        for i in range(5):
            min = random.randint(20, 48)
            a2 = random.randint(0, 30)
            a2m = random.randint(0, a2)
            a3 = random.randint(0, 20)
            a3m = random.randint(0, a3)
            al = random.randint(0, 16)
            alm = random.randint(0, al)
            pase = random.randint(0, 25)
            recup = random.randint(0, 10)
            fault = random.randint(0, 5)
            query = f"insert into statistici values(idseq.nextval, {idmeci}, {idhome_player+i}, " \
                    f"{min}, {a2}, {a2m}, {a3}, {a3m}, {al}, {alm}, {pase}, {recup}, {fault});"
            print(query, file=f)

        for i in range(5):
            min = random.randint(20, 48)
            a2 = random.randint(0, 30)
            a2m = random.randint(0, a2)
            a3 = random.randint(0, 20)
            a3m = random.randint(0, a3)
            al = random.randint(0, 16)
            alm = random.randint(0, al)
            pase = random.randint(0, 25)
            recup = random.randint(0, 10)
            fault = random.randint(0, 5)
            query = f"insert into statistici values(idseq.nextval, {idmeci}, {idaway_player + i}, " \
                    f"{min}, {a2}, {a2m}, {a3}, {a3m}, {al}, {alm}, {pase}, {recup}, {fault});"
            print(query, file=f)


nr_premii = 5
id_premiu = 1476
def insertPremii():
    with open('insert-premii.txt', 'w') as f:
        for i in range(nr_premii):
            denumire = awards[i]
            query = f"insert into premii values(idseq.nextval, '{denumire}');"
            print(query, file=f)


def insertParticipari():
    with open('insert-participari.txt', 'w') as f:
        for i in range(nr_echipe):
            query = f"insert into participari values({id_sezon}, {id_echipa + i});"
            print(query, file=f)


def insertArbitraje():
    with open('insert-arbitraje.txt', 'w') as f:
        for i in range(nr_meciuri):
            id1 = id_arbitru + random.randint(0, nr_arbitrii - 1)
            id2 = id_arbitru + random.randint(0, nr_arbitrii - 1)
            while id2 == id1:
                id2 = id_arbitru + random.randint(0, nr_arbitrii - 1)
            id3 = id_arbitru + random.randint(0, nr_arbitrii - 1)
            while id3 == id2 or id3 == id1:
                id3 = id_arbitru + random.randint(0, nr_arbitrii - 1)

            query = f"insert into arbitraje values({id_meci + i}, {id1});"
            print(query, file=f)
            query = f"insert into arbitraje values({id_meci + i}, {id2});"
            print(query, file=f)
            query = f"insert into arbitraje values({id_meci + i}, {id3});"
            print(query, file=f)


def insertComentarii():
    with open('insert-comentarii.txt', 'w') as f:
        for i in range(nr_meciuri):
            id1 = id_comentator + random.randint(0, nr_comentatori - 1)
            id2 = id_comentator + random.randint(0, nr_comentatori - 1)
            while id2 == id1:
                id2 = id_comentator + random.randint(0, nr_comentatori - 1)
            id3 = id_comentator + random.randint(0, nr_comentatori - 1)
            while id3 == id2 or id3 == id1:
                id3 = id_comentator + random.randint(0, nr_comentatori - 1)

            query = f"insert into comentarii values({id_meci + i}, {id1});"
            print(query, file=f)
            query = f"insert into comentarii values({id_meci + i}, {id2});"
            print(query, file=f)
            query = f"insert into comentarii values({id_meci + i}, {id3});"
            print(query, file=f)


def insertDistinctii():
    with open('insert-distinctii.txt', 'w') as f:
        for idsez in range(id_sezon, id_sezon + nr_sezoane):
            for idpr in range(id_premiu, id_premiu + nr_premii):
                juc = id_jucator + random.randint(0, nr_jucatori_ech * nr_echipe - 1)
                query = f"insert into distinctii values({idsez}, {juc}, {idpr});"
                print(query, file=f)


insertSezoane()
insertEtape()
insertAngajati()
insertAntrenori()
insertPreparatoriFizici()
insertNutritionisti()
insertLocatii()
insertArene()
insertEchipe()
insertJucatori()
insertEchipeMedicale()
insertMeciuri()
insertArbitrii()
insertComentatori()
insertStatistici()
insertPremii()
insertParticipari()
insertArbitraje()
insertComentarii()
insertDistinctii()
