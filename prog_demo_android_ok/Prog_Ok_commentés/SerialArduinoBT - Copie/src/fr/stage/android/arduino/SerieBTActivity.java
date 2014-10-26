package fr.stage.android.arduino;

import android.app.Activity;
import android.app.ProgressDialog;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;


public class SerieBTActivity extends Activity implements OnClickListener
{
  private TextView distance;
  private TextView direction;
  private TextView accelerationX;
  private TextView accelerationY;
  private TextView accelerationZ;
  private TextView temperature;
  private TextView humidite;
  private TextView pollution;
  private TextView logview;
  private EditText sendtext;
  private Button connect, disconnect;
  private ScrollView  sv;
  private BtInterface bt            = null;
  private long        lastTime      = 0;
  ProgressDialog      mProgressDialog;
  // handler qui gere l'affichage dans le thread de l'UI
  final Handler       gestionDonnees = new Handler()
                                    {
                                      public void handleMessage(Message msg)
                                      {
                                        String data = msg.getData().getString(
                                            "receivedData");
                                        long t = System.currentTimeMillis();
                                        if (t - lastTime > 100)
                                        {// Pour éviter que les messages ne soit
                                         // coupés
                                          logview.append("\n");
                                          lastTime = System.currentTimeMillis();
                                        }
                                        logview.append(data);
                                        sv.fullScroll(View.FOCUS_DOWN);
                                        Log.d("test","chaine="+data);
                                        // Mise à jour des données
                                        // temperature
                                        // On recherche la chaine "TEMP"
                                        int startIndex = data.indexOf("TEMP");
                                        // si elle est trouvée startIndex est sa position
                                        // dans la chaine "data"
                                        if (startIndex != -1)
                                        {	
                                          // On recherche la fin de l'information du capteur
                                          // caracterisee par "\r"
                                          int stopIndex = data.indexOf("\r",startIndex);
                                          // si elle est trouvée stopIndex indique sa postion
                                          // dans la chaine data
                                          if(stopIndex != -1)
                                        	  // affichage de la valeur contenue entre "TEMP"
                                        	  // et "\r"
                                        	  temperature.setText(data
                                                  .substring(startIndex + 4,stopIndex));
                                        }
                                        // humidite
                                        startIndex = data.indexOf("HUMI");
                                        if (startIndex != -1)
                                        {	
                                            int stopIndex = data.indexOf("\r",startIndex);
                                            if(stopIndex != -1)
                                          	  humidite.setText(data
                                                    .substring(startIndex + 4,stopIndex));
                                        }
                                        //distance
                                        startIndex = data.indexOf("DIST");
                                        if (startIndex != -1)
                                        {	
                                            int stopIndex = data.indexOf("\r",startIndex);
                                            if(stopIndex != -1)
                                          	  distance.setText(data
                                                    .substring(startIndex + 4,stopIndex));
                                        }
                                        //boussole
                                        startIndex = data.indexOf("ANGL");
                                        if (startIndex != -1)
                                        {	
                                            int stopIndex = data.indexOf("\r",startIndex);
                                            if(stopIndex != -1)
                                          	  direction.setText(data
                                                    .substring(startIndex + 4,stopIndex));
                                        }
                                        //acceleration sur X
                                        startIndex = data.indexOf("ACCX");
                                        if (startIndex != -1)
                                        {	
                                            int stopIndex = data.indexOf("_",startIndex);
                                            if(stopIndex != -1)
                                          	  accelerationX.setText("Axe X: "+data
                                                    .substring(startIndex + 4,stopIndex));
                                              
                                            
                                        }
                                      //acceleration sur Y
                                        startIndex = data.indexOf("ACCY");
                                        if (startIndex != -1)
                                        {	
                                            int stopIndex = data.indexOf("_",startIndex);
                                            if(stopIndex != -1)
                                            
                                              accelerationY.setText("Axe Y: "+data
                                                     .substring(startIndex + 4,stopIndex));
          
                                 
                                        }
                                      //acceleration sur Z
                                        startIndex = data.indexOf("ACCZ");
                                        if (startIndex != -1)
                                        {	
                                            int stopIndex = data.indexOf("\r",startIndex);
                                            if(stopIndex != -1)
                                          	  accelerationZ.setText("Axe Z: "+data
                                                    .substring(startIndex + 4,stopIndex));
                                        }
                                        startIndex = data.indexOf("QAIR");
                                        if (startIndex != -1)
                                        {	
                                            int stopIndex = data.indexOf("\r",startIndex);
                                            if(stopIndex != -1)
                                          	  pollution.setText(data
                                                    .substring(startIndex + 4,stopIndex));
                                        }
                                      } 
                                    };
// handler qui gere les debut/maintient/fin de la communication bluetooth
  final Handler      statutConnexion = new Handler()
                                    {
                                      public void handleMessage(Message msg)
                                      {
                                        int co = msg.arg1;
                                        if (co == 1)
                                        {
                                          logview.append("Connected\n");
                                          // faire disparaitre la fenetre de chargement
                                          mProgressDialog.dismiss();
                                        }
                                        else if (co == 2)
                                        {
                                          logview.append("Disconnected\n");
                                        }
                                      }
                                    };

  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    // initialisation du socket bluetooth
    // il faut préalablement associer l'appareil Android avec
    // le module bluetooth
    bt = new BtInterface(statutConnexion, gestionDonnees);
    logview = (TextView) findViewById(R.id.logview);
    logview.setTextColor(Color.GRAY);
    connect = (Button) findViewById(R.id.connexionBt);
    connect.setTextColor(Color.CYAN);
    connect.setOnClickListener(this);
    disconnect = (Button) findViewById(R.id.disconnect);
    disconnect.setTextColor(Color.RED);
    disconnect.setOnClickListener(this);
    temperature = (TextView) findViewById(R.id.textTemperature);
    temperature.setTextColor(Color.CYAN);
    humidite = (TextView) findViewById(R.id.textHumidite);
    humidite.setTextColor(Color.CYAN);
    distance = (TextView) findViewById(R.id.textUltrason);
    distance.setTextColor(Color.CYAN);
    direction = (TextView) findViewById(R.id.textBoussole);
    direction.setTextColor(Color.CYAN);
    accelerationX = (TextView) findViewById(R.id.textAccelerationX);
    accelerationX.setTextColor(Color.CYAN);
    accelerationY = (TextView) findViewById(R.id.textAccelerationY);
    accelerationY.setTextColor(Color.CYAN);
    accelerationZ = (TextView) findViewById(R.id.textAccelerationZ);
    accelerationZ.setTextColor(Color.CYAN);
    pollution = (TextView) findViewById(R.id.textPollution);
    pollution.setTextColor(Color.CYAN);
    sv = (ScrollView) findViewById(R.id.sv);
    //
  }

  @Override
  public void onClick(View v)
  {
    if (v == connect)
    {
      // l'utilisateur clique sur le bouton "Connection"
      bt.connect();
      // barre de chargement en attendant la connexion
      mProgressDialog = ProgressDialog.show(this, "Patientez",
          "Connexion bluetooth...", true);
    }
    if (v == disconnect)
    {
      // l'utilisateur clique sur le bouton "Connection"
      bt.close();
    }
  }
}