-- Exercitiul 6 - COLECTII
create or replace procedure ex6_colectii 
as
    -- Am ales tabloul imbricat deoarece numarul de sezoane este necunoscut 
    -- si nu fac stergeri pe parcursul programului
    type IdSezoane is table of sezoane.id_sezon%type ;
    id_sezoane IdSezoane;
    id_sezon_curent sezoane.id_sezon%type;
    
    -- Am ales varray deoarece stiu dinainte numarul de etape (30) dintr-un sezon,
    -- respectiv numarul de meciuri dintr-o etapa (8), si nu fac stergeri in aceasta colectie
    type IdEtape is varray(30) of etape.id_etapa%type;
    id_etape IdEtape;
    id_etapa_curenta sezoane.id_sezon%type;
    
    type RecordJucator is record
     (
         id_jucator jucatori.id_jucator%type,
         puncte number
    );
    type idJucatoriTop3 is varray(3) of RecordJucator;
    id_jucatori_3 IdJucatoriTop3;
    rec RecordJucator;
    
    -- Am ales tablou indexat deoarece indicii vor fi anumite id-uri ale jucatorilor, nu neaparat dense.
    type TabelPuncteJucatori is table of number(4) index by pls_integer;
    puncte_jucator TabelPuncteJucatori;
    
    nr_etape number; -- restriciile spun ca pentru fiecare sezon exista 30 etape
    
    maxim number;
    id_mvp jucatori.id_jucator%type;
    jucator jucatori%rowtype;
    
begin
    select id_sezon bulk collect into id_sezoane from sezoane;
    
    for it_sezon in id_sezoane.first..id_sezoane.last loop
        id_sezon_curent := id_sezoane(it_sezon);
        select count(id_etapa) collect into nr_etape 
        from etape
        where id_sezon = id_sezon_curent;
        
        if nr_etape != 30
        then 
            dbms_output.put_line ('In sezonul ' || id_sezon_curent || 
            ' nu sunt 30 de etape ( ' || nr_etape || ' )');
            continue;
        end if;
        
        select id_etapa bulk collect into id_etape 
        from etape
        where id_sezon = id_sezon_curent;
        
        maxim := 0;
        for it_etapa in id_etape.first..id_etape.last loop
            id_etapa_curenta := id_etape(it_etapa);
            with jucatori_si_puncte as
                (select j.id_jucator, 2 * aruncari_2pct_marcate + 3 * aruncari_3pct_marcate + aruncari_libere_marcate
                from jucatori j
                join meciuri m on m.id_etapa = id_etapa_curenta and
                    ((m.id_echipa_gazda = j.id_echipa and scor_gazda >  scor_oaspete ) or
                    (m.id_echipa_oaspete = j.id_echipa and scor_gazda <  scor_oaspete ))
                join statistici s on s.id_meci = m.id_meci and s.id_jucator = j.id_jucator
                order by 2 desc)
            select * bulk collect into id_jucatori_3
            from jucatori_si_puncte
            where rownum <= 3;
        
            for it in id_jucatori_3.first..id_jucatori_3.last loop
                rec := id_jucatori_3(it);
                if puncte_jucator.exists(rec.id_jucator) = false
                then puncte_jucator(rec.id_jucator) := 0;
                end if;
        
                puncte_jucator(rec.id_jucator) := puncte_jucator(rec.id_jucator) + rec.puncte;
                 if maxim < puncte_jucator(rec.id_jucator)
                then
                    maxim := puncte_jucator(rec.id_jucator);
                    id_mvp := rec.id_jucator;
                end if;
            end loop;
        end loop;
        
        select * into jucator
        from jucatori
        where id_jucator = id_mvp;
        
        dbms_output.put_line(jucator.nume || ' ' || jucator.prenume || '  id: ' || id_mvp || ' puncte:  ' || puncte_jucator(id_mvp));
        
    end loop;
        
end;
/

begin
    ex6_colectii();
end;
/
