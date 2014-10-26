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
    // On r�cup�re la liste des p�riph�riques associ�s � notre appareil Android
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
          // On utilise cet UUID pour une connection s�rie
          // On cr�� un socket bluetooth pour notre p�riph�rique
          socket = device.createRfcommSocketToServiceRecord(UUID
              .fromString("00001101-0000-1000-8000-00805F9B34FB"));
          // flux de r�ception (fonctionnera d�s que la connection est �tablie)
          receiveStream = socket.getInputStream();
          // flux d'�mission (fonctionnera d�s que la connection est �tablie)
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
    // on pr�pare le thread de r�ception des donn�es
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
      // On �crit les donn�es dans le buffer d'envoi
      sendStream.write(data.getBytes());
      // On s'assure qu'elles soient bien envoy�s
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
          // r�ussite de connection: envoie un msg pour afficher "Connected"
          statutConnexion.sendMessage(msg);
          // on d�marre le thread de r�ception des donn�es
          processusReception.start();
        }
        catch (IOException e)
        {
          // �chec de la connection
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
          // r�ussite de connection: envoie un msg pour afficher "DisConnected"
          statutConnexion.sendMessage(msg);
        }
        catch (IOException e)
        {
          // �chec de la connection
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
    // Thread qui re�oit les donn�es re�ues par le module BT
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
              // donn�es de r�ception � l'�cran ( gestionDonnees )
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
