package lab6.marker.exc;

public class TestTransformable {
    public static void main(String[] args) throws NotTransformableException {
        Bumblebee bumblebee = new Bumblebee("blue", true);
        Sofa sofa = new Sofa("red", 10);

        System.out.println(Transformer.transform(bumblebee));
        System.out.println(Transformer.transform(sofa));
    }
}
