using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace MAI
{
    class FileOperations
    {
        // Loads object from file
        public static object FileToObject(string _FileName)
        {
            try
            {
                // Open file for reading
                System.IO.FileStream _FileStream = new System.IO.FileStream(_FileName, System.IO.FileMode.Open, System.IO.FileAccess.Read);

                // attach filestream to binary reader
                System.IO.BinaryReader _BinaryReader = new System.IO.BinaryReader(_FileStream);

                // get total byte length of the file
                long _TotalBytes = new System.IO.FileInfo(_FileName).Length;

                // read entire file into buffer
                byte[] _ByteArray = _BinaryReader.ReadBytes((Int32)_TotalBytes);

                // close file reader and do some cleanup
                _FileStream.Close();
                _FileStream.Dispose();
                _FileStream = null;
                _BinaryReader.Close();

                // convert byte array to memory stream
                System.IO.MemoryStream _MemoryStream = new System.IO.MemoryStream(_ByteArray);

                // create new BinaryFormatter
                System.Runtime.Serialization.Formatters.Binary.BinaryFormatter _BinaryFormatter
                            = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();

                // set memory stream position to starting point
                _MemoryStream.Position = 0;

                // Deserializes a stream into an object graph and return as a object.
                return _BinaryFormatter.Deserialize(_MemoryStream);
            }
            catch (Exception _Exception)
            {
                // Error
                Console.WriteLine("Exception caught in process: {0}", _Exception.ToString());
            }

            // Error occured, return null
            return null;
        }

        // Saves object to a file
        public static bool ObjectToFile(object _Object, string _FileName)
        {
            try
            {
                // create new memory stream
                System.IO.MemoryStream _MemoryStream = new System.IO.MemoryStream();

                // create new BinaryFormatter
                System.Runtime.Serialization.Formatters.Binary.BinaryFormatter _BinaryFormatter
                            = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();

                // Serializes an object, or graph of connected objects, to the given stream.
                _BinaryFormatter.Serialize(_MemoryStream, _Object);

                // convert stream to byte array
                byte[] _ByteArray = _MemoryStream.ToArray();

                // Open file for writing
                System.IO.FileStream _FileStream = new System.IO.FileStream(_FileName, System.IO.FileMode.Create, System.IO.FileAccess.Write);

                // Writes a block of bytes to this stream using data from a byte array.
                _FileStream.Write(_ByteArray.ToArray(), 0, _ByteArray.Length);

                // close file stream
                _FileStream.Close();

                // cleanup
                _MemoryStream.Close();
                _MemoryStream.Dispose();
                _MemoryStream = null;
                _ByteArray = null;

                return true;
            }
            catch (Exception _Exception)
            {
                // Error
                Console.WriteLine("Exception caught in process: {0}", _Exception.ToString());
            }

            // Error occured, return null
            return false;
        }

        public static bool writeText(String s, String path)
        {
            try{
                using (StreamWriter w = File.AppendText(path))
                {
                    w.Write("\r\n" + s);
                }
                return true;
            }
            catch (Exception _Exception){
                Console.Out.WriteLine("Error Occurred: {0}", _Exception);
                return false;
            }
        }

        public static String readText(String path)
        {
            // The files used in this example are created in the topic 
            // How to: Write to a Text File. You can change the path and 
            // file name to substitute text files of your own. 

            // Example #1 
            // Read the file as one string. 
            string text = System.IO.File.ReadAllText(path);

            return text;
        }

        public static String[] readTextLines(String path)
        {
            // Example #2 
            // Read each line of the file into a string array. Each element 
            // of the array is one line of the file. 
            string[] lines = System.IO.File.ReadAllLines(path);
            return lines;
        }

    }
}
