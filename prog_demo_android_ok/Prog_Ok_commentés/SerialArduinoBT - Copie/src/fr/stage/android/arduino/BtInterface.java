package fr.stage.android.arduino;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class BtInterface
{
  private BluetoothDevice device        = null;
  private BluetoothSocket socket        = null;
  private InputStream     receiveStream = null;
  private OutputStream    sendStream    = null;
  private ReceiverThread  processusReception;
  Handler                 statutConnexion;

  public BtInterface(Handler connexion, Handler manageData)
  {
    // On récupère la liste des périphériques associés à notre appareil Android
    Set<BluetoothDevice> setpairedDevices = BluetoothAdapter
        .getDefaultAdapter().getBondedDevices();
    BluetoothDevice[] pairedDevices = (BluetoothDevice[]) setpairedDevices
        .toArray(new BluetoothDevice[setpairedDevices.size()]);
    for (int i = 0; i < pairedDevices.length; i++)
    {
      // Notre module bluetooth doit contenir le nom 'ModuleBluetooth'
      if (pairedDevices[i].getName().contains("SeeedBTSlave"))
      {
        device = pairedDevices[i];
        try
        {
          // On utilise cet UUID pour une connection série
          // On créé un socket bluetooth pour notre périphérique
          socket = device.createRfcommSocketToServiceRecord(UUID
              .fromString("00001101-0000-1000-8000-00805F9B34FB"));
          // flux de réception (fonctionnera dès que la connection est établie)
          receiveStream = socket.getInputStream();
          // flux d'émission (fonctionnera dès que la connection est établie)
          sendStream = socket.getOutputStream();
        }
        catch (IOException e)
        {
          e.printStackTrace();
        }
        break;
      }
    }
    statutConnexion = connexion;
    // on prépare le thread de réception des données
    processusReception = new ReceiverThread(manageData);
  }

  public void sendData(String data)
  {
    sendData(data, false);
  }

  public void sendData(String data, boolean deleteScheduledData)
  {
    try
    {
      // On écrit les données dans le buffer d'envoi
      sendStream.write(data.getBytes());
      // On s'assure qu'elles soient bien envoyés
      sendStream.flush();
    }
    catch (IOException e)
    {
      e.printStackTrace();
    }
  }

  public void connect()
  {
    new Thread()
    {
      @Override
      public void run()
      {
        try
        {
          // tentive de connection
          socket.connect();
          Message msg = statutConnexion.obtainMessage();
          msg.arg1 = 1;
          // réussite de connection: envoie un msg pour afficher "Connected"
          statutConnexion.sendMessage(msg);
          // on démarre le thread de réception des données
          processusReception.start();
        }
        catch (IOException e)
        {
          // échec de la connection
          Log.v("N", "Connection Failed : " + e.getMessage());
          e.printStackTrace();
        }
      }
    }.start();
  }

  public void close()
  {
    new Thread()
    {
      @Override
      public void run()
      {
        try
        {
          // tentive de connection
          socket.close();
          Message msg = statutConnexion.obtainMessage();
          msg.arg1 = 2;
          // réussite de connection: envoie un msg pour afficher "DisConnected"
          statutConnexion.sendMessage(msg);
        }
        catch (IOException e)
        {
          // échec de la connection
          Log.v("N", "Connection Failed : " + e.getMessage());
          e.printStackTrace();
        }
      }
    }.start();
  }

  public BluetoothDevice getDevice()
  {
    return device;
  }

  private class ReceiverThread extends Thread
  {
    // Thread qui reçoit les données reçues par le module BT
    Handler handler;

    ReceiverThread(Handler h)
    {
      handler = h;
    }

    @Override
    public void run()
    {
      while (true)
      {
        try
        {
          // si il y a des donnees sur le canal de reception	
          if (receiveStream.available() > 0)
          {
        	// tableau d'octets de 100 cases  
            byte buffer[] = new byte[100];
            // on stocke les donnees dans le tableau, k prend la valeur du nb de cases remplies
            int k = receiveStream.read(buffer, 0, 100);
            // si il y a des donnes
            if (k > 0)
            {
              // tableau d'octet qui a pour longueur le nombre de case de "buffer"
              byte rawdata[] = new byte[k];
              // chaque donnee de "buffer" est stockee dans "rawdata"
              for (int i = 0; i < k; i++)
                rawdata[i] = buffer[i];
              // on convertit "rawdata" en chaine de caracteres
              String data = new String(rawdata);
              // on recupere le "Message" du handler
              Message msg = handler.obtainMessage();
              // creation d'une variable transmissible dans le "Message"
              Bundle b = new Bundle();
              // on stocke les donnees que l'on appelle "receivedData" qui remplace les anciennes
              b.putString("receivedData", data);
              // on edite le "Message" avec le bundle cree et complete
              msg.setData(b);
              // envoie du message au SerieBTActivity pour qu'il affiche les
              // données de réception à l'écran ( gestionDonnees )
              handler.sendMessage(msg);
            }
          }
        }
        catch (IOException e)
        {
          e.printStackTrace();
        }
      }
    }
  }
}
