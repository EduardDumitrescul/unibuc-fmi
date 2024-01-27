-- Exercitiul 7 - CURSOARE

create or replace procedure ex7_cursoare
is
    cursor c_id_arbitri (idm meciuri.id_meci%type) is
        select id_arbitru from arbitraje where arbitraje.id_meci = idm;
        
        
    type IdArbitri is table of arbitrii.id_arbitru%type;
    id_arbitri IdArbitri;
    arbitru arbitrii%rowtype;
        
    cursor meciuriVerificate is
        select *
        from meciuri
        where abs(scor_gazda - scor_oaspete) =  
            (select max(abs(scor_gazda - scor_oaspete))
             from meciuri);
             
        cursor arbitriVerificati (idm meciuri.id_meci%type) is
            select *
            from arbitrii
           where id_arbitru in (select id_arbitru from arbitraje where arbitraje.id_meci = idm);
           
        cursor jucatoriMeci (
        id_gazda echipe.id_echipa%type,
        id_oaspete echipe.id_echipa%type, 
        nume_arbitru arbitrii.nume%type) is
            select id_jucator , nume, prenume, id_echipa
            from jucatori 
            where (id_echipa = id_gazda or id_echipa = id_oaspete)
            and jucatori.nume = nume_arbitru;
            
        mesaj varchar2(50);
        id_echipa echipe.id_Echipa%type;
begin
    
    -- CICLU CURSOR
    for meci in meciuriVerificate loop
--        dbms_output.put_line('meci: ' || meci.id_meci);

        -- CURSOR CLASIC PARAMETRIZAT
        open c_id_arbitri(meci.id_meci);
        fetch c_id_arbitri bulk collect into id_arbitri;
        close c_id_arbitri;
        
        for i in id_arbitri.first..id_arbitri.last loop
            select * into arbitru
            from arbitrii
            where id_arbitru = id_arbitri(i);
--            dbms_output.put_line('arbitru: ' || arbitru.id_arbitru);
            -- CICLU CURSOR PARAMETRIZAT
            for jucator in jucatoriMeci(meci.id_echipa_gazda, meci.id_echipa_oaspete, arbitru.nume) loop
            
                if meci.scor_gazda > meci.scor_oaspete
                then id_echipa := meci.id_echipa_gazda;
                else id_echipa := meci.id_echipa_oaspete;
                end if;
                
                if jucator.id_echipa = id_echipa
                then mesaj := ' (Victorie)';
                else mesaj := ' (Infrangere)';
                end if;
            
                dbms_output.put_line(meci.id_meci || ': ' ||
                    arbitru.id_arbitru || ' ' || arbitru.nume || ' ' || arbitru.prenume || ' - ' ||
                    jucator.id_jucator || ' ' || jucator.nume || ' ' || jucator.prenume || ' - ' || 
                    meci.scor_gazda || '-' || meci.scor_oaspete || mesaj);
            
                end loop;
        end loop;
    end loop;
    
end;
/

begin
    ex7_cursoare();
end;
/
