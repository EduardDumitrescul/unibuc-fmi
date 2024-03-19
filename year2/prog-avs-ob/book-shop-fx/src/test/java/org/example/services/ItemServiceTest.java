package org.example.services;

import org.example.data.Seeder;
import org.example.data.models.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class ItemServiceTest {
    private ItemService itemService = ItemService.getInstance();

    @BeforeEach
    public void setUp() {
        Seeder.seed();
    }
    @Test
    void getItem() {
        Item item = itemService.getItem(4);
        if(item instanceof Book) {
            System.out.println("book");
        }
        else if(item instanceof ColoringBook) {
            System.out.println("drawing book");
        }
        else if(item instanceof Notebook) {
            System.out.println("notebook");
        }
        else if(item instanceof Cookbook) {
            System.out.println("cookbook");
        }
        else {
            System.out.println("item");
        }
    }
}