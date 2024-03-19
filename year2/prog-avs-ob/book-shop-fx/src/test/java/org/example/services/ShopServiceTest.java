package org.example.services;

import org.example.data.Seeder;
import org.example.data.models.InventoryItem;
import org.example.data.models.Item;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.List;

class ShopServiceTest {
    private ShopService shopService = ShopService.getInstance();

    @BeforeEach
    void setUp() {
        Seeder.seed();
    }

    @Test
    void getItemsByInventoryIdTest() {
        List<InventoryItem> items = shopService.getItemsByInventoryId(1);
        System.out.println(items);
    }
    @Test
    void getAllItem() {
        List<Item> items = shopService.getAllItems();
        System.out.println(items);
    }

    @Test
    void addItemToInventory() {
        List<InventoryItem> items = shopService.getItemsByInventoryId(1);
        System.out.println(items);
        shopService.addItemToShopInventory(1, 1);
        items = shopService.getItemsByInventoryId(1);
        System.out.println(items);
    }

    @Test
    void userBuysItem() {
        shopService.buyItem(1, 1, 1);

    }
}