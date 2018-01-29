
let make = (~body, ~styles, ~title, ()) => {j|
  <!DOCTYPE html>
    <html>
      <head>
        <title>$title</title>
        $styles
      </head>
      
      <body>
        <div id="root">$body</div>
      </body>
    </html> 
|j};

let generateStyles = (~html="", ()) => {
  let css = Nice.extract(html).css
  |> List.fold_left((a, b) => a ++ " " ++ b, "");

  {j|<style type="text/css">$css</style>|j};
};
