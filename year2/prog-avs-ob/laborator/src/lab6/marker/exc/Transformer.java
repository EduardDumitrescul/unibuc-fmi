package lab6.marker.exc;

public class Transformer {
    public static String transform(Object object) throws NotTransformableException {
        if(!(object instanceof Transformable)) {
            throw new NotTransformableException();
        }   
        return "transformable";

    }
}
