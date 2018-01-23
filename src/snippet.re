type t = {
  id: int,
  content: string,
  description: string,
  example: string,
  jsOutput: string
};

let workingReDir = "./snippets/";
let workingJsDir = "./lib/js/snippets/";

let listSnippetNames = () => {
  Node.Fs.readdirSync(workingReDir)
  |> Array.map(name => String.sub(name, 0, String.length(name) - 3));
};

let loadSnippetRawRe = name => {
  Node.Fs.readFileAsUtf8Sync(workingReDir ++ name ++ ".re")
};

let loadSnippetJsOutput = name => {
  Node.Fs.readFileAsUtf8Sync(workingJsDir ++ name ++ ".bs.js");
};

let toJson = snippet => {
  let snippetJson = Js.Dict.empty();
  Js.Dict.set(snippetJson, "id", Js.Json.number(float_of_int(snippet.id)));
  Js.Dict.set(snippetJson, "content", Js.Json.string(snippet.content));
  Js.Dict.set(snippetJson, "description", Js.Json.string(snippet.description));
  Js.Dict.set(snippetJson, "example", Js.Json.string(snippet.example));
  Js.Dict.set(snippetJson, "jsOutput", Js.Json.string(snippet.jsOutput));
  Js.Json.object_(snippetJson);
};

let createSnippet = (~id, ~rawRe, ~jsOutput, ()) => {
  let pattern = [%bs.re "/(\\/\\* @description )([\\s\\S]*)(\\*\\/)([\\s\\S]*)(\\/\\* @content \\*\\/)([\\s\\S]*)(\\/\\* @example \\*\\/)([\\s\\S]*)/"];
  /* God i hate regex in Reason */
  let segments = switch (Js.Re.exec(rawRe, pattern)) {
  | None => [||];
  | Some(result) => result
    |> Js.Re.captures
    |> Array.map(Js.Nullable.to_opt)
    |> Array.map(segment => switch segment {
      | None => ""
      | Some(x) => x
    })
  };
  switch segments {
  | [| _all, _descHeader, description, _descEnd, _setup, _contentHeader, content, _exampleHeader, example |] => {
      id,
      description: String.trim(description),
      content: String.trim(content),
      example: String.trim(example),
      jsOutput
    }
  | _ => { id: -1, description: "", content: "", example: "", jsOutput: "" }
  };
};

let loadSnippets = () => {
  listSnippetNames()
  |> Array.mapi((i, name) => createSnippet(
    ~id=i,
    ~rawRe=loadSnippetRawRe(name),
    ~jsOutput=loadSnippetJsOutput(name),
    ()))
  |> Array.to_list
  |> List.filter(snippet => snippet.id === -1 ? false : true)
};

