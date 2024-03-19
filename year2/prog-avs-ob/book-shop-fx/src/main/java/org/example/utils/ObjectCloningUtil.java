package org.example.utils;

import org.example.data.entities.ItemEntity;

import java.util.ArrayList;
import java.util.List;

public class ObjectCloningUtil {
    private ObjectCloningUtil() {}

    public static  List<ItemEntity> cloneList(List<ItemEntity> items) {
        List<ItemEntity> list = new ArrayList<>();
        for(ItemEntity obj: items) {
            list.add(obj.clone());
        }
        return list;
    }


}
