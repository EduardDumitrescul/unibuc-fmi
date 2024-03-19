package org.example.services;

import org.example.data.entities.InventoryItemCrossRef;
import org.example.data.entities.ItemEntity;
import org.example.data.entities.ShopEntity;
import org.example.data.entities.UserEntity;
import org.example.data.mappers.ItemMapper;
import org.example.data.models.InventoryItem;
import org.example.data.models.Item;
import org.example.data.repositories.*;

import java.util.ArrayList;
import java.util.List;

public class ShopService {
    private ShopRepository shopRepository = ShopRepository.getInstance();
    private InventoryRepository inventoryRepository = InventoryRepository.getInstance();
    private ItemInventoryCrossRefRepository itemInventoryCrossRefRepository = ItemInventoryCrossRefRepository.getInstance();
    private ItemRepository itemRepository = ItemRepository.getInstance();

    private UserRepository userRepository = UserRepository.getInstance();

    public List<InventoryItem> getItemsByInventoryId(int inventoryId) {
        try {
            List<InventoryItemCrossRef> inventoryItemCrossRefs = itemInventoryCrossRefRepository.getItemsByInventoryId(inventoryId);
            List<InventoryItem> items = new ArrayList<>();
            for(InventoryItemCrossRef entity: inventoryItemCrossRefs) {
                ItemEntity itemEntity = itemRepository.getById(entity.itemId);
                Item item = ItemMapper.asItem(itemEntity);
                items.add(new InventoryItem(item, entity.count));
            }
            return items;
        }
        catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return new ArrayList<>();
    }

    private boolean itemExistsInInventory(int inventoryId, int itemId) {
        return itemInventoryCrossRefRepository.getInventoryItem(inventoryId, itemId) != null;
    }

    public void buyItem(int shopId, int userId, int itemId) {
        removeItemFromShopInventory(shopId, itemId);
        addItemToUserInventory(userId, itemId);
    }

    public void removeItemFromShopInventory(int shopId, int itemId) {
        ShopEntity shopEntity = shopRepository.getById(shopId);
        int inventoryId = shopEntity.inventoryId;
        InventoryItemCrossRef inventoryItemCrossRef = itemInventoryCrossRefRepository.getInventoryItem(inventoryId, itemId);
        if(inventoryItemCrossRef.count  == 1) {
            itemInventoryCrossRefRepository.delete(inventoryItemCrossRef);
        }
        else {
            inventoryItemCrossRef.count -= 1;
            itemInventoryCrossRefRepository.update(inventoryItemCrossRef);
        }

    }

    private void addItemToUserInventory(int userId, int itemId) {
        ItemEntity itemEntity = itemRepository.getById(itemId);
        int newItemId = itemRepository.addItem(itemEntity);
        UserEntity userEntity = userRepository.getUser(userId);
        itemInventoryCrossRefRepository.add(new InventoryItemCrossRef(userEntity.inventoryId, newItemId, 1));
    }

    public void addItemToShopInventory(int itemId, int shopId) {
        ShopEntity shopEntity = shopRepository.getById(shopId);
        int inventoryId = shopEntity.inventoryId;
        if(itemExistsInInventory(inventoryId, itemId)) {
            InventoryItemCrossRef inventoryItemCrossRef = itemInventoryCrossRefRepository.getInventoryItem(inventoryId, itemId);
            inventoryItemCrossRef.count += 1;
            itemInventoryCrossRefRepository.update(inventoryItemCrossRef);
        }
        else {
            itemInventoryCrossRefRepository.add(new InventoryItemCrossRef(inventoryId, itemId, 1));
        }

    }

    public List<Item> getAllItems() {
        List<ItemEntity> entities =  itemRepository.getAll();
        List<Item> items = entities.stream().map(ItemMapper::asItem).toList();
        return items;
    }


    private ShopService() {}

    private static ShopService instance = null;

    public static ShopService getInstance() {
        if(instance == null) {
            instance = new ShopService();
        }
        return instance;
    }
}
