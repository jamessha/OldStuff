using System;
/// <summary>
/// RSS manager to read rss feeds
/// </summary>
public static class RssManager
{
    /// <summary>
    /// Reads the relevant Rss feed and returns a list off RssFeedItems
    /// </summary>
    /// <param name="url"></param>
    /// <returns></returns>
    /// 
    String url = "http:////finance.yahoo.com//q?s={0}";
    ArrayList<String> url_list = new ArrayList<string>();
    ArrayList<String> stock_list = new ArrayList<String>();

    public RssManager()
    {
        stock_list.add("aapl");
        foreach (String ticker in stock_list)
        {
            url_list.add(System.String.Format(url, ticker));
        }

        Console.Out.WriteLine(url_list.get(0));
    }

    static void main (String[] args)
    {
        RssManager newManager = new RssManager();
    }

    public static List<RssFeedItem> ReadFeed(string url)
    {
        //create a new list of the rss feed items to return
        List<RssFeedItem> rssFeedItems = new List<RssFeedItem>();

        //create an http request which will be used to retrieve the rss feed
        HttpWebRequest rssFeed = (HttpWebRequest)WebRequest.Create(url);

        //use a dataset to retrieve the rss feed
        using (DataSet rssData = new DataSet())
        {
            //read the xml from the stream of the web request
            rssData.ReadXml(rssFeed.GetResponse().GetResponseStream());

            //loop through the rss items in the dataset and populate the list of rss feed items
            foreach (DataRow dataRow in rssData.Tables["item"].Rows)
            {
                rssFeedItems.Add(new RssFeedItem
                {
                    ChannelId = Convert.ToInt32(dataRow["channel_Id"]),
                    Description = Convert.ToString(dataRow["description"]),
                    ItemId = Convert.ToInt32(dataRow["item_Id"]),
                    Link = Convert.ToString(dataRow["link"]),
                    PublishDate = Convert.ToDateTime(dataRow["pubDate"]),
                    Title = Convert.ToString(dataRow["title"])
                });
            }
        }

        //return the rss feed items
        return rssFeedItems;
    }
}
