package org.example.services;

import org.example.data.entities.InventoryEntity;
import org.example.data.entities.InventoryItemCrossRef;
import org.example.data.entities.ItemEntity;
import org.example.data.entities.UserEntity;
import org.example.data.mappers.ItemMapper;
import org.example.data.models.Item;
import org.example.data.models.User;
import org.example.data.models.UserInventory;
import org.example.data.repositories.InventoryRepository;
import org.example.data.repositories.ItemInventoryCrossRefRepository;
import org.example.data.repositories.ItemRepository;
import org.example.data.repositories.UserRepository;

import java.util.List;

public class UserService {
    private UserRepository userRepository = UserRepository.getInstance();
    private InventoryRepository inventoryRepository = InventoryRepository.getInstance();
    private ItemInventoryCrossRefRepository itemInventoryCrossRefRepository = ItemInventoryCrossRefRepository.getInstance();

    private ItemRepository itemRepository = ItemRepository.getInstance();

    private User currentUser = null;
    private UserService() {}
    public boolean isUnique(String username) {
        return !userRepository.usernameExists(username);
    }

    public boolean usernameExists(String username) {return userRepository.usernameExists(username); }

    public void register(String username, String password) throws Exception {
        if(isUnique(username)) {
            InventoryEntity inventory = new InventoryEntity(0);
            int inventoryId = inventoryRepository.add(inventory);

            UserEntity user = new UserEntity(0, username, password, inventoryId);

            int userId = userRepository.add(user);

            currentUser = getUserById(userId);
        }
        else {
            throw new Exception("Username is already in use");
        }
    }

    public User getUserById(int id) {
        UserEntity userEntity = userRepository.getUser(id);
        UserInventory userInventory = getInventoryById(userEntity.inventoryId);

        User user = new User(userEntity.id, userEntity.username, userEntity.password, userInventory);
        return user;
    }

    public List<Item> getItemsByInventoryId(int inventoryId) {
        List<InventoryItemCrossRef> inventoryItemCrossRefs = itemInventoryCrossRefRepository.getItemsByInventoryId(inventoryId);
        List<Integer> itemIds = inventoryItemCrossRefs.stream().map(e -> e.itemId).toList();
        List<ItemEntity> itemEntities = itemRepository.getById(itemIds);
        List<Item> items = itemEntities.stream().map(ItemMapper::asItem).toList();
        return items;
    }

    public UserInventory getInventoryById(int id) {
        InventoryEntity inventoryEntity = inventoryRepository.getById(id);
        List<Item> items = getItemsByInventoryId(inventoryEntity.id);

        UserInventory userInventory = new UserInventory(inventoryEntity.id, items);
        return userInventory;
    }

    public boolean passwordIsCorrect(String username, String password) {
        UserEntity entity = userRepository.findUserByUsername(username);
        return entity.password.equals(password);
    }

    public void login(String username, String password) throws Exception {
        if(!usernameExists(username)) {
            throw new Exception("Username does not exist!");
        }
        if(!passwordIsCorrect(username, password)) {
            throw new Exception("Password is incorrect!");
        }
        UserEntity entity  = userRepository.findUserByUsername(username);
        currentUser = getUserById(entity.id);
    }

    public void throwAwayItem(int userId, int itemId) {
        UserEntity userEntity = userRepository.getUser(userId);
        InventoryItemCrossRef inventoryItemCrossRef = itemInventoryCrossRefRepository.getInventoryItem(userEntity.inventoryId, itemId);
        itemInventoryCrossRefRepository.delete(inventoryItemCrossRef);
    }


    private static UserService instance = null;
    public static UserService getInstance() {
        if(instance == null) {
            instance = new UserService();
        }
        return instance;
    }

    public boolean isLoggedIn() {
        return currentUser != null;
    }
}
