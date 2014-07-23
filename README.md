##Drive DJ

The eventual goal of this may be an app that coordinates with a music player with a navigation app (e.g. Spotify w/ Google Maps) and make a playlist that automatically makes it so that your last song finishes as you pull in to your destination.

Right now song lists wil be imported from sample song data and driving times will be randomly specified. The algorithms will be compared based on time it takes to create the playlist, and how close the playlist time is to the travelling time.

####Ideas for Methods of Sorting
- Adding random songs until reaching a certain point. Then swapping songs in and out until the playlist is within the time window.
- Splitting the songs up into several groups and identifying them by their average time. Build playlist based on averages, then select songs below or above the average in order to make the time window.

####Possible Future Features
- [ ] Include rating field for each song and judge playlists by "likeability" 
   - possibly using a Knapsack Sorting Method: http://en.wikipedia.org/wiki/Knapsack_problem

