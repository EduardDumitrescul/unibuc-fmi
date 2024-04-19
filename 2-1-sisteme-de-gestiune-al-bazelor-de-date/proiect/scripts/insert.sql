-- Exercitiul 5 - INSERT

create or replace  function get_id    
    return number is
        f_id number;
    begin
        select idseq.nextval into f_id
        from dual;
        return f_id;
    end;
/


create or replace function prenume_aleator
return varchar2 as 
    prenume  varchar2(20);  
    type StringArray is varray(20) of varchar2(20);
    lista_prenume StringArray := StringArray(
        'Ethan', 'Isaac', 'Leo', 'Miles', 'Asher',
         'Maxwell', 'Oscar', 'Dylan', 'Oliver', 'Harrison',
         'Nathan', 'Gabriel', 'Jasper', 'Ezra', 'Silas',
        'Sebastian', 'Caleb', 'Gideon', 'Wyatt', 'Finn'
    );
begin
    prenume := lista_prenume(dbms_random.value(1, lista_prenume.last));
    return prenume;
end;
/

create or replace function nume_aleator
return varchar2 as 
    nume  varchar2(20);  
    type StringArray is varray(50) of varchar2(20);
    lista_nume StringArray := StringArray('Smith', 'Johnson', 'Williams', 'Jones', 'Brown', 
    'Davis', 'Miller', 'Wilson', 'Moore', 'Taylor', 'Anderson', 'Thomas', 'Jackson',
    'White', 'Harris', 'Martin', 'Thompson', 'Garcia', 'Martinez', 'Robinson', 'Clark', 
    'Rodriguez', 'Lewis', 'Lee', 'Walker', 'Hall', 'Allen', 'Young', 'Hernandez', 'King', 
    'Wright', 'Lopez', 'Hill', 'Scott', 'Green', 'Adams', 'Baker', 'Gonzalez', 'Nelson',
    'Carter', 'Mitchell', 'Perez', 'Roberts', 'Turner', 'Phillips', 'Campbell', 'Parker', 'Evans', 'Edwards');


begin
    nume := lista_nume(dbms_random.value(1, lista_nume.last));
    return nume;
end;
/

begin
    <<sterge_date>>
    begin
        delete from arbitraje;
        delete from comentarii;
        delete from distinctii;
        delete from participari;
    
    
        delete from premii;
        delete from statistici;
    
        delete from arbitrii;
        delete from comentatori;
        delete from meciuri;
        delete from echipe_medicale;
    
        delete from jucatori;
        delete from echipe;
        delete from arene;
        delete from locatii;
    
        delete from preparatori_fizici;
        delete from nutritionisti;
        delete from antrenori;
        delete from angajati;
    
        delete from etape;
        delete from sezoane;
    end;


    <<insert_sezoane>>
    declare
        v_numar_sezoane number := 5;
        v_format_data varchar2(11) := 'dd-mon-yyyy';
        v_data_start date := to_date('15-aug-2022',v_format_data);
        v_data_final date := to_date('10-jun-2023', v_format_data);
        sezon sezoane%rowtype;
    begin
        sezon.data_incepere := v_data_start;
        sezon.data_finalizare := v_data_final;
        sezon.id_sezon := get_id();
        for cnt in 1..v_numar_sezoane
        loop
            insert into sezoane
            values sezon;
            sezon.data_incepere := add_months(sezon.data_incepere, -12);
            sezon.data_finalizare := add_months(sezon.data_finalizare, -12);
            sezon.id_sezon := get_id();
        end loop;
        
        dbms_output.put_line('insert_sezoane OK');
    end;
    
    <<insert_etape>>
    declare
        v_numar_etape number := 30;
        type id_sezoane is table of sezoane.id_sezon%type index by pls_integer;
        v_id_sezoane id_sezoane; 
        v_etapa etape%rowtype;
    begin
        select id_sezon
        bulk collect into v_id_sezoane
        from sezoane;
        
        for cnt_sezon in v_id_sezoane.first..v_id_sezoane.last
        loop
            for cnt_etapa in 1..v_numar_etape
            loop
                v_etapa.id_etapa := get_id();
                v_etapa.id_sezon := v_id_sezoane(cnt_sezon);
                v_etapa.numar := cnt_etapa;
                insert into etape
                values v_etapa;
             end loop;
        end loop;
        dbms_output.put_line('insert_etape OK');
    end;

    <<insert_antrenori>>
    declare
        numar_antrenori number := 16;
        angajat angajati%rowtype;
        antrenor antrenori%rowtype;
    begin
        for i in 1..numar_antrenori
        loop
            angajat.id_angajat := get_id();
            angajat.nume := nume_aleator();
            angajat.prenume := prenume_aleator();
            angajat.salariu  := 100 * dbms_random.value(100, 200);
            antrenor.id_angajat := angajat.id_angajat;
            
            insert into angajati values angajat;
            insert into antrenori values antrenor;
        end loop;
        dbms_output.put_line('insert_antrenori OK');
    end;
    
    <<insert_preparatori>>
    declare
        numar_preparatori number := 16;
        angajat angajati%rowtype;
        preparator preparatori_fizici%rowtype;
    begin
        for i in 1..numar_preparatori
        loop
            angajat.id_angajat := get_id();
            angajat.nume := nume_aleator();
            angajat.prenume := prenume_aleator();
            angajat.salariu  := 100 * dbms_random.value(100, 200);
            preparator.id_angajat := angajat.id_angajat;
            
            insert into angajati values angajat;
            insert into preparatori_fizici values preparator;
        end loop;
        dbms_output.put_line('insert_preparatori OK');
    end;
    
    <<insert_nutritionisti>>
    declare
        numar_nutritionisti number := 16;
        angajat angajati%rowtype;
        nutritionist nutritionisti%rowtype;
    begin
        for i in 1..numar_nutritionisti
        loop
            angajat.id_angajat := get_id();
            angajat.nume := nume_aleator();
            angajat.prenume := prenume_aleator();
            angajat.salariu  := 100 * dbms_random.value(100, 200);
            nutritionist.id_angajat := angajat.id_angajat;
            
            insert into angajati values angajat;
            insert into nutritionisti values nutritionist;
        end loop;
        dbms_output.put_line('insert_nutritionisti OK');
    end;

    <<insert_locatii>>
    declare
        type StringArray is varray(16) of varchar2(30);
        orase StringArray := StringArray('New York City', 'Los Angeles','Las Vegas',
        'Chicago', 'San Francisco', 'Miami', 'Orlando', 'Houston','Seattle', 
        'Washington D.C.', 'Boston', 'Atlanta', 'Dallas', 'Denver',  
        'New Orleans', 'San Diego');
        strazi StringArray := StringArray('Fifth Avenue', 'Hollywood Boulevard', 
        'Las Vegas Boulevard', 'Michigan Avenue', 'Lombard Street', 
        'Ocean Drive', 'International Drive', 'NASA Road 1', 'Pike Place Market', 
        '1600 Pennsylvania Avenue NW', 'Fenway Park',  'Peachtree Street', 
        'Dealey Plaza', '16th Street Mall', 'Bourbon Street', 'Balboa Park');
        locatie locatii%rowtype;
        nr_locatii number := 16;
    begin
        for i in 1..nr_locatii
        loop
            locatie.id_locatie := get_id();
            locatie.tara := 'USA';
            locatie.oras := orase(i);
            locatie.strada := strazi(i);
            locatie.nr := dbms_random.value(100, 1000);
            insert into locatii values locatie;
        end loop;
        dbms_output.put_line('insert_locatii OK');
    end;
    
    <<insert_arene>>
    declare
        type IdLocatii is table of locatii.id_locatie%type index by pls_integer;
        id_locatii IdLocatii;
        numar_arene number := 16;
        type StringArray is varray(16) of varchar2(30);
        lista_arene StringArray := StringArray('The Thunderdome', 'The Coliseum', 'The Pit', 
        'The Garden',  'The Staples Center', 'The Oracle', 'The Hoop House', 'The Den',
                   'The Arena', 'The Thunderdome', 'The Dome', 'The Palace',
                   'The Madhouse', 'The Pavilion', 'The Buzzer Beater', 'The Swish Center');
        arena arene%rowtype;
    begin
        select id_locatie
        bulk collect into id_locatii
        from locatii;
        
        for i in 1..numar_arene
        loop
            arena.id_arena := get_id();
            arena.id_locatie := id_locatii(i);
            arena.nume := lista_arene(i);
            arena.locuri := 1000 * dbms_random.value(10, 20);
            
            insert into arene values arena;
        end loop;
        dbms_output.put_line('insert_arene OK');
    end;
    
    <<insert_echipe>>
    declare
        type StringArray is varray(16) of varchar2(20);
        lista_nume StringArray := StringArray('Lightning Bolts', 'Thunderbirds', 
        'Wildcats', 'Heatwave', 'Hurricanes', 'Jaguars', 'Patriots', 'Titans',
              'Vikings', 'Dragons', 'Raptors', 'Warriors',
              'Hornets', 'Sharks', 'Lions', 'Knights');
        
        type IdTable is table of number index by pls_integer;
        id_arene IdTable;
        id_antrenori IdTable;
        id_preparatori IdTable;
        id_nutritionisti IdTable;
        echipa echipe%rowtype;
        numar_echipe number := 16;
    begin
        select id_arena bulk collect into id_arene from arene;
        select id_angajat bulk collect into id_antrenori from antrenori;
        select id_angajat bulk collect into id_preparatori from preparatori_fizici;
        select id_angajat bulk collect into id_nutritionisti from nutritionisti;
    
        for i in 1..numar_echipe
        loop
            echipa.id_echipa := get_id();
            echipa.id_arena := id_arene(i);
            echipa.id_antrenor := id_antrenori(i);
            echipa.id_preparator := id_preparatori(i);
            echipa.id_nutritionist := id_nutritionisti(i);
            echipa.nume := lista_nume(i);
            echipa.an_infiintare := 1960 + dbms_random.value(0, 30);
            
            insert into echipe values echipa;
        end loop;
        dbms_output.put_line('insert_echipe OK');
    end;    
    
    <<insert_jucatori>>
    declare
        type IdArray is table of echipe.id_echipa%type index by pls_integer;
        id_echipe IdArray;
        id_echipa echipe.id_echipa%type;
        jucator jucatori%rowtype;
        numar_jucatori_per_echipa number := 5;
    begin
        select id_echipa bulk collect into id_echipe from echipe;
        
        for i in id_echipe.first..id_echipe.last
        loop
            id_echipa := id_echipe(i);
            for i in 1..numar_jucatori_per_echipa
            loop
                jucator.id_jucator := get_id();
                jucator.id_echipa := id_echipa;
                jucator.nume := nume_aleator();
                jucator.prenume := prenume_aleator();
                jucator.inaltime := dbms_random.value(1.80, 2.25);
                jucator.salariu := 1000 * dbms_random.value(40, 100);
                
                insert into jucatori values jucator;
            end loop;
        end loop;
        
        dbms_output.put_line('insert_jucatori OK');
    end;
    
    <<insert_echipe_medicale>>
    declare
        numar_echipe_medicale number := 5;
    begin
        for i in 1..numar_echipe_medicale
        loop 
            insert into echipe_medicale values(get_id());
        end loop;
        
        dbms_output.put_line('insert_echipe_medicale OK');
    end;
    
    <<insert_meciuri>>
    declare
        type IdArray is table of number index by pls_integer;
        id_sezoane IdArray;
        id_echipe IdArray;
        id_echipe_med IdArray;
        id_etape IdArray;
        meci meciuri%rowtype;
        type IntArray is varray(8) of number;
        x1 IntArray := IntArray(1, 2, 3, 4, 5, 6, 7, 8);
        x2 IntArray := IntArray(16, 15, 14, 13, 12, 11, 10, 9);
        rev boolean := false;
        id_gazda number;
        id_oaspete number;
        temp number;
        ids sezoane.id_sezon%type;
    begin
        select id_sezon bulk collect into id_sezoane from sezoane;
        select id_echipa bulk collect into id_echipe from echipe;
        select id_echipa_medicala bulk collect into id_echipe_med from echipe_medicale;
    
        
        
        for i in id_sezoane.first..id_sezoane.last
        loop
            ids := id_sezoane(i);
             select id_etapa bulk collect into id_etape 
             from etape
             where id_sezon = ids;
             
            for nr_etapa in 1..30
            loop
                for i in 1..8
                loop
                    if rev = false
                    then 
                        id_gazda := id_echipe(x1(i));
                        id_oaspete := id_echipe(x2(i));
                    else
                        id_gazda := id_echipe(x2(i));
                        id_oaspete := id_echipe(x1(i));
                    end if;
                    
                    meci.id_meci := get_id();
                    meci.id_etapa := id_etape(nr_etapa);
                    meci.id_echipa_gazda := id_gazda;
                    meci.id_echipa_oaspete := id_oaspete;
                    meci.id_echipa_medicala := id_echipe_med(dbms_random.value(1, id_echipe_med.last));
                    meci.scor_gazda := dbms_random.value(60, 100);
                    meci.scor_oaspete := meci.scor_gazda + (dbms_random.value(0, 94) - 47);
                    
                    insert into meciuri values meci;
                    
                end loop;
                temp := x2(1);
                for i in 1..7
                loop
                    x2(i) := x2(i+1);
                end loop;
                x2(8) := x1(8);
                for i in reverse 3..8
                loop
                    x1(i) := x1(i-1);
                end loop;
                x1(2) := temp;
                
                if x1(2) = 2
                then rev := true;
                end if;
                
            end loop;
        end loop;
    end;    
    
    <<insert_arbitrii>>
    declare
        arbitru arbitrii%rowtype;
        numar_arbitrii number := 50;
    begin
        for i in 1..numar_arbitrii
        loop
            arbitru.nume := nume_aleator();
            arbitru.prenume := prenume_aleator();
            arbitru.id_arbitru := get_id();
            arbitru.data_obtinere_licenta := to_date(trunc(
                   dbms_random.value(to_char(date '1990-01-01','J') ,to_char(date '2015-12-31','J') )
                   ),'J' );
                insert into arbitrii values arbitru;
        end loop;
        
        dbms_output.put_line('insert_arbitrii OK');
    end;
    
     <<insert_comentatori>>
    declare
        comentator comentatori%rowtype;
        numar_comentatori number := 10;
    begin
        for i in 1..numar_comentatori
        loop
            comentator.nume := nume_aleator();
            comentator.prenume := prenume_aleator();
            comentator.id_comentator := get_id();
             insert into comentatori values comentator;
        end loop;
        
        dbms_output.put_line('insert_comentatori OK');
    end;
    

    <<insert_statistici>>
    declare
        type IdArray is table of number index by pls_integer;
        id_meciuri IdArray;
        id_jucatori IdArray;
        statistica statistici%rowtype;
        meci meciuri%rowtype;
        idm meciuri.id_meci%type;
        idj jucatori.id_jucator%type;
    begin
        select id_meci bulk collect into id_meciuri from meciuri;
        
        for i in id_meciuri.first..id_meciuri.last
        loop
            idm := id_meciuri(i);
             select * into meci from meciuri where id_meci = idm;
            select id_jucator bulk collect into id_jucatori
            from jucatori
            where id_echipa = meci.id_echipa_gazda or id_echipa = meci.id_echipa_oaspete;
            
            for j in id_jucatori.first..id_jucatori.last
            loop
                idj := id_jucatori(j);
                statistica.id_statistica := get_id();
                statistica.id_meci := idm;
                statistica.id_jucator := idj;
                statistica.minute_jucate := dbms_random.value(20, 48);
                statistica.aruncari_2pct := dbms_random.value(0, 30);
                statistica.aruncari_2pct_marcate := dbms_random.value(0, statistica.aruncari_2pct);
                statistica.aruncari_3pct := dbms_random.value(0, 20);
                statistica.aruncari_3pct_marcate := dbms_random.value(0, statistica.aruncari_3pct);
                statistica.aruncari_libere := dbms_random.value(0, 10);
                statistica.aruncari_libere_marcate := dbms_random.value(0, statistica.aruncari_libere);
                statistica.pase_decisive := dbms_random.value(0, 25);
                statistica.recuperari := dbms_random.value(0,15);
                statistica.faulturi := dbms_random.value(0, 5);
                
                insert into statistici values statistica;
            end loop;
        end loop;
        
        dbms_output.put_line('insert_statistica OK');
    end;
            
    <<insert_premii>>
    declare
        type StringArray is varray(5) of varchar2(50);
        lista_premii StringArray := StringArray('Most Valuable Player (MVP)', 
        'Team Player of the Year',
          'Defensive Player of the Year', 'Sportsmanship Award', 'Best Distance Shooter');
          premiu premii%rowtype;
        begin
            for i in lista_premii.first..lista_premii.last
            loop
                premiu.id_premiu := get_id();
                premiu.denumire := lista_premii(i);
                insert into premii values premiu;
            end loop;
            
            dbms_output.put_line('inser_premii OK');
        end;
          
    <<insert_participari>>
    declare
         type IdArray is table of number index by pls_integer;
        id_sezoane IdArray;
        id_echipe IdArray;
        participare participari%rowtype;
        ids sezoane.id_sezon%type;
        ide echipe.id_echipa%type;
    begin
        select id_sezon bulk collect into id_sezoane from sezoane;
        select id_echipa bulk collect into id_echipe from echipe;
    
        for i in id_sezoane.first..id_sezoane.last
        loop
            ids := id_sezoane(i);
            for j in id_echipe.first..id_echipe.last
            loop
                ide := id_echipe(j);
                participare.id_sezon := ids;
                participare.id_echipa := ide;
                insert into participari values participare;
            end loop;
        end loop;
        
        dbms_output.put_line('insert_participari OK');
    end;
        
    <<insert_comentarii>>
    declare
        comentariu comentarii%rowtype;
        type IdArray is table of number index by pls_integer;
        id_meciuri IdArray;
        id_comentatori IdArray;
        a number(2,0);
        b number(2,0);
        c number(2,0);
    begin
        select id_meci bulk collect into id_meciuri from meciuri;
        select id_comentator bulk collect into id_comentatori from comentatori;
        
        for i in id_meciuri.first..id_meciuri.last
        loop
            a := dbms_random.value(1,id_comentatori.last);
            b := dbms_random.value(1,id_comentatori.last);
            c := dbms_random.value(1,id_comentatori.last);
            while a = b
            loop
                b := dbms_random.value(1,id_comentatori.last);
            end loop;
            while a = c or b = c
            loop
                c := dbms_random.value(1,id_comentatori.last);
            end loop;
            comentariu.id_meci := id_meciuri(i);
            comentariu.id_comentator := id_comentatori(a);
            insert into comentarii values comentariu;
             comentariu.id_comentator := id_comentatori(b);
            insert into comentarii values comentariu;
            comentariu.id_comentator := id_comentatori(c);
            insert into comentarii values comentariu;
        end loop;
      
      dbms_output.put_line('insert-comentarii OK');
    end;
    
    <<insert_arbitraje>>
    declare
        arbitraj arbitraje%rowtype;
        type IdArray is table of number index by pls_integer;
        id_meciuri IdArray;
        id_arbitrii IdArray;
        a number(2,0);
        b number(2,0);
        c number(2,0);
    begin
        select id_meci bulk collect into id_meciuri from meciuri;
        select id_arbitru bulk collect into id_arbitrii from arbitrii;
        
        for i in id_meciuri.first..id_meciuri.last
        loop
            a := dbms_random.value(1,id_arbitrii.last);
            b := dbms_random.value(1,id_arbitrii.last);
            c := dbms_random.value(1,id_arbitrii.last);
            while a = b
            loop
                b := dbms_random.value(1,id_arbitrii.last);
            end loop;
            while a = c or b = c
            loop
                c := dbms_random.value(1,id_arbitrii.last);
            end loop;
            arbitraj.id_meci := id_meciuri(i);
            arbitraj.id_arbitru := id_arbitrii(a);
            insert into arbitraje values arbitraj;
             arbitraj.id_arbitru := id_arbitrii(b);
            insert into arbitraje values arbitraj;
            arbitraj.id_arbitru := id_arbitrii(c);
            insert into arbitraje values arbitraj;
        end loop;
      
      dbms_output.put_line('insert-arbitraje OK');
    end;
    
    <<insert_distinctii>>
    declare
        distinctie distinctii%rowtype;
        type IdArray is table of number index by pls_integer;
        id_sezoane IdArray;
        id_jucatori IdArray;
        id_premii IdArray;
    begin
        select id_sezon bulk collect into id_sezoane from sezoane;
        select id_jucator bulk collect into id_jucatori from jucatori;
        select id_premiu bulk collect into id_premii from premii;
        
        for i in id_sezoane.first..id_sezoane.last
        loop
            for j in id_premii.first..id_premii.last
            loop
                distinctie.id_sezon := id_sezoane(i);
                distinctie.id_premiu := id_premii(j);
                distinctie.id_jucator := id_jucatori(dbms_random.value(1, id_jucatori.last));
                
                insert into distinctii values distinctie;
            end loop;
        end loop;
        
        dbms_output.put_line('insert_distinctii OK');
    end;
        
    <<verifica_inserare>>
    declare
        cnt number;
        type StringArray is varray(20) of varchar2(20);
        tabele StringArray := StringArray('angajati', 'antrenori', 'arbitrii', 
        'arene', 'comentarii', 'comentatori', 'distinctii', 'echipe', 
        'echipe_medicale', 'etape', 'jucatori', 'locatii', 
        'meciuri', 'nutritionisti', 'participari', 'premii', 'preparatori_fizici', 
        'sezoane', 'statistici');
    begin
        select count(*) into cnt from angajati;
        dbms_output.put_line('Exista ' || cnt || ' angajati.');
        select count(*) into cnt from antrenori;
        dbms_output.put_line('Exista ' || cnt || ' antrenori.');   
        select count(*) into cnt from arbitraje;
        dbms_output.put_line('Exista ' || cnt || ' arbitraje.');
        select count(*) into cnt from arbitrii;
        dbms_output.put_line('Exista ' || cnt || ' arbitrii.');
         select count(*) into cnt from arene;
        dbms_output.put_line('Exista ' || cnt || ' arene.');
        select count(*) into cnt from comentarii;
        dbms_output.put_line('Exista ' || cnt || ' comentarii.');   
            select count(*) into cnt from comentatori;
        dbms_output.put_line('Exista ' || cnt || ' comentatori.');   
        select count(*) into cnt from distinctii;
        dbms_output.put_line('Exista ' || cnt || ' distinctii.');
        select count(*) into cnt from echipe;
        dbms_output.put_line('Exista ' || cnt || ' echipe.');
        select count(*) into cnt from echipe_medicale;
        dbms_output.put_line('Exista ' || cnt || ' echipe_medicale.');
        select count(*) into cnt from etape;
        dbms_output.put_line('Exista ' || cnt || ' etape.');   
        select count(*) into cnt from jucatori;
        dbms_output.put_line('Exista ' || cnt || ' jucatori.');
        select count(*) into cnt from locatii;
        dbms_output.put_line('Exista ' || cnt || ' locatii.');
         select count(*) into cnt from meciuri;
        dbms_output.put_line('Exista ' || cnt || ' meciuri.');
        select count(*) into cnt from nutritionisti;
        dbms_output.put_line('Exista ' || cnt || ' nutritionisti.');   
        select count(*) into cnt from participari;
        dbms_output.put_line('Exista ' || cnt || ' participari.');
        select count(*) into cnt from premii;
        dbms_output.put_line('Exista ' || cnt || ' premii.');
        select count(*) into cnt from preparatori_fizici;
        dbms_output.put_line('Exista ' || cnt || ' preparatori_fizici.');   
        select count(*) into cnt from sezoane;
        dbms_output.put_line('Exista ' || cnt || ' sezoane.');
        select count(*) into cnt from statistici;
        dbms_output.put_line('Exista ' || cnt || ' statistici.');
       
    end;
    dbms_output.put_line('OK');
end;
/
