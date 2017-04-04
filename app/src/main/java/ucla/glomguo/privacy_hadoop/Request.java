package ucla.glomguo.privacy_hadoop;
import java.io.Serializable;
import java.util.HashMap;

/**
 * Created by Lui on 6/4/16.
 */

public class Request implements Serializable {
    public final String type;
    public final HashMap<String, IPStatus> map;

    public Request(String type, HashMap<String, IPStatus> map){
        this.type = type;
        this.map = map;
    }
}