type dataObject = {
  .
  "__typename": string,
  "id": string,
  "key": string
};

let cache = ApolloInMemoryCache.createInMemoryCache(~dataIdFromObject=(obj: dataObject) => obj##id, ());

type schema('a) = {. "resolvers": {. "Query": 'a }, "typeDefs": string } ;

[@bs.module "graphql-tools"]
external addMockFunctionsToSchema : {. "schema": schema('a)} => schema('a) = "addMockFunctionsToSchema";

[@bs.module "graphql-tools"]
external makeExecutableSchema : {. "typeDefs": string} => schema(unit) = "makeExecutableSchema";

let schema = {
  let executableSchema = makeExecutableSchema({"typeDefs": Graphql.types});
  addMockFunctionsToSchema({"schema": executableSchema});
};

let link = ApolloLinkSchema.make({"schema": schema});

module Client =
  ReasonApollo.CreateClient(
    {
      let apolloClient = ReasonApollo.createApolloClient(~cache, ~link, ~ssrMode=Js.Boolean.to_js_boolean(true), ());
    }
  );
