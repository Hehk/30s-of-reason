open Express;

let app = express();

let makeSuccessJson = () => {
  let json = Js.Dict.empty();
  Js.Dict.set(json, "hello", Js.Json.string("reason"));
  Js.Json.object_(json)
};

App.useOnPath(app, ~path="/", Middleware.from(
  (_req, res, _next) => {
    Response.sendJson(res, makeSuccessJson());
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
