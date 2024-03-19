package org.example.data.mappers;

import org.example.data.entities.*;
import org.example.data.models.*;

public class ItemMapper {
    private ItemMapper() {}

    public static Item asItem(ItemEntity entity) {
        return new Item(entity.getId(), entity.getPrice());
    }

    public static Book asBook(ItemEntity itemEntity, BookEntity bookEntity) {
        return new Book(
                itemEntity.id,
                itemEntity.price,
                bookEntity.title,
                bookEntity.author,
                bookEntity.numberOfPages,
                bookEntity.numberOfPagesRead
        );
    }

    public static ColoringBook asDrawingBook(ItemEntity itemEntity, ColoringBookEntity coloringBookEntity) {
        return new ColoringBook(
                itemEntity.id,
                itemEntity.price,
                coloringBookEntity.theme,
                coloringBookEntity.numberOfDrawings,
                coloringBookEntity.numberOfDrawingCompleted
        );
    }

    public static Notebook asNotebook(ItemEntity itemEntity, NotebookEntity notebookEntity) {
        return new Notebook(
                itemEntity.id,
                itemEntity.price,
                notebookEntity.type,
                notebookEntity.numberOfPages,
                notebookEntity.numberOfPagesWritten
        );
    }

    public static Cookbook asCookbook(ItemEntity itemEntity, CookbookEntity cookbookEntity) {
        return new Cookbook(
                itemEntity.id,
                itemEntity.price,
                cookbookEntity.skillLevel,
                cookbookEntity.numberOfRecipes,
                cookbookEntity.numberOfRecopesTried
        );
    }
}
