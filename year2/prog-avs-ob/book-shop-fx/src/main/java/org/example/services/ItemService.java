package org.example.services;

import org.example.data.entities.*;
import org.example.data.mappers.ItemMapper;
import org.example.data.models.Item;
import org.example.data.repositories.*;

public class ItemService {
    private ItemRepository itemRepository = ItemRepository.getInstance();
    private BookRepository bookRepository = BookRepository.getInstance();
    private ColoringBookRepository coloringBookRepository = ColoringBookRepository.getInstance();
    private NotebookRepository notebookRepository = NotebookRepository.getInstance();

    private CookbookRepository cookbookRepository = CookbookRepository.getInstance();

    public Item getItem(int id) {
        ItemEntity itemEntity = itemRepository.getById(id);
        Item item;

        if(bookRepository.exists(id)) {
            BookEntity bookEntity = bookRepository.getById(id);
            item = ItemMapper.asBook(itemEntity, bookEntity);
        }
        else if(coloringBookRepository.exists(id)) {
            ColoringBookEntity coloringBookEntity = coloringBookRepository.getById(id);
            item = ItemMapper.asDrawingBook(itemEntity, coloringBookEntity);
        }
        else if(notebookRepository.exists(id)) {
            NotebookEntity notebookEntity = notebookRepository.getById(id);
            item = ItemMapper.asNotebook(itemEntity, notebookEntity);
        }
        else if(cookbookRepository.exists(id)) {
            CookbookEntity cookbookEntity = cookbookRepository.getById(id);
            item = ItemMapper.asCookbook(itemEntity, cookbookEntity);
        }
        else {
            item = ItemMapper.asItem(itemEntity);
        }

        return item;
    }

    private static ItemService instance = null;
    private ItemService() {}

    public static ItemService getInstance() {
        if(instance == null) {
            instance = new ItemService();
        }
        return instance;
    }
}
