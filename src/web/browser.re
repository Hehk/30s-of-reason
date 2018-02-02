[@bs.val] [@bs.module "react-dom"] external hydrate : (ReasonReact.reactElement, Dom.element) => unit = "hydrate";

[@bs.val] [@bs.return nullable] external _getElementById : string => option(Dom.element) = "document.getElementById";

let hydrateToElementWithId = (reactElement, id) =>
  switch (_getElementById(id)) {
  | None =>
    raise(Invalid_argument("ReactDOMRE.renderToElementWithId : no element of id " ++ (id ++ " found in the HTML.")))
  | Some(element) => hydrate(reactElement, element)
  };

hydrateToElementWithId(<App />, "react-root");
