open Express;

let app = express();
let snippets = Snippet.loadSnippets();

let makeSnippetListJson = () => {
  let json = Js.Dict.empty();
  Js.Dict.set(json, "snippets", Js.Json.array(
    Array.map(Snippet.toJson, snippets)
  ));
  Js.Json.object_(json)
};

App.useOnPath(app, ~path="/", Middleware.from(
  (_req, res, _next) => {
    Response.sendJson(res, makeSnippetListJson());
  }
));

let onListen = (port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log("Listening at localhost:" ++ string_of_int(port))
  };

App.listen(app, ~onListen=onListen(3000), ());
