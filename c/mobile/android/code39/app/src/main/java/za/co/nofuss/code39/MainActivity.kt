package za.co.nofuss.code39

import android.graphics.Bitmap
import android.os.Bundle
import android.util.DisplayMetrics
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity
import java.util.Locale


class MainActivity : AppCompatActivity() {
    private val tag = MainActivity::class.java.simpleName
    private var etBarcode: EditText? = null
    private var ivBarcode: ImageView? = null
    private var bBarcode: Button? = null

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String? // created by new application wizard
    external fun code39(
        text: String?,
        bitmap: Bitmap?
    ) // our function to generate code 3 of 9 bar code symbol

    // END NATIVE CODE RELATED
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        bBarcode = findViewById(R.id.bBarcode)
        bBarcode.setOnClickListener(View.OnClickListener {
            val textOfInterest =
                "*" + etBarcode!!.text.toString().uppercase(Locale.getDefault()) + "*"
            Log.i(tag, "clicked! [$textOfInterest]")
            val displayMetrics = DisplayMetrics()
            windowManager.defaultDisplay.getMetrics(displayMetrics)
            val height = displayMetrics.heightPixels
            val width = displayMetrics.widthPixels
            val bitmapWip = Bitmap.createBitmap(width - 20, 100, Bitmap.Config.ALPHA_8)
            code39(textOfInterest, bitmapWip)
            ivBarcode!!.setImageBitmap(bitmapWip)
        })
        etBarcode = findViewById(R.id.etBarcode)
        ivBarcode = findViewById(R.id.ivBarcode)

        // Example of a call to a native method
        //TextView tv = findViewById(R.id.sample_text);
        //tv.setText(stringFromJNI());
    }

    companion object {
        // BEGIN NATIVE CODE RELATED
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}