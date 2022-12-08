<div align="center">

<!--prettier-ignore-->
[Overview](https://github.com/jcbhmr/wordle#readme)
| **[Dev wiki](https://github.com/jcbhmr/wordle/tree/main/wiki)**
| [packages/fetch](https://github.com/jcbhmr/wordle/tree/main/packages/fetch#readme)
| [packages/html-location](https://github.com/jcbhmr/wordle/tree/main/packages/html-location#readme)

</div>

The official Wordle game is available on the New York Times' website at
[nytimes.com/games/wordle]. In Wordle, there are two lists of words:

1. A list of valid user guesses
2. An ordered list of daily wordle answers

The importance of the first list is to ensure that the user is actually guessing
a possible word. If that list weren't there, users could guess "aaaaa" which
should obviously not be accepted.

The second list is the most important; it tells you which word to place in the
answer slot for each day. There's also a date offset for when "Wordle #0"
occured. For the official NYT version, Wordle #0 happened on June 19th, 2021 as
shown by the [Wordle Archive].

The official word list can be extracted from the public JavaScript code that the
game `index.html` imports. On 2022-12-08, this happens to be
https://www.nytimes.com/games-assets/v2/wordle.56c55094fe33b9362bc133efd958582107f17a39.js,
but the code has moved around in the past.

<div align="center">

![](https://i.imgur.com/ND9aSEL.png)

</div>

ℹ As of 2022-12-08, the list of valid guesses and daily Wordles are combined
into a single JSON array. Make sure you split them up! You can tell which is
which by the alphabetical ordering.

📜 Historical: [Retrieve the wordle word list from the JS Source Code] from
2022-01-24

[nytimes.com/games/wordle]: https://www.nytimes.com/games/wordle/index.html
[wordle archive]: https://game8.co/games/Wordle/archives/369779
[retrieve the wordle word list from the js source code]:
  https://www.youtube.com/watch?v=4VxYGeiFqK4
