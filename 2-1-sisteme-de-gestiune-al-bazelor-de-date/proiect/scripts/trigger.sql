-- Exercitiul 11 - Trigger LMD Linie

create or replace trigger verifica_max30etape_sezon
before insert on etape
for each row
declare
    nr_etape number := 0;
    
    etapa etape%rowtype;
begin
    select count(*) into nr_etape
    from etape 
    where id_sezon = :new.id_sezon;
    
     if nr_etape >= 30 then
        raise_application_error(-20001, 'Nu poate fi adaugata etapa deoarece sezonul contine deja numarul maxim (30)');
    end if;
    
    select * into etapa
    from etape
    where id_sezon = :new.id_sezon and numar = :new.numar;
    
    if etapa.id_etapa is not null then
        raise_application_error(-20000, 'Nu poate fi adaugata etapa deoarece sezonul contine o etapa cu acelasi numar');
    end if;
    
exception
    when no_data_found then
        nr_etape := 0;
end;
/

-- max 30
 insert into etape values (1, 1000, 1); 
    
-- etapa cu acelasi numar
insert into sezoane values (10000, '', '');
insert into etape values(10016, 10000, 6);
insert into etape values(10015, 10000, 6);

